package toyLanguage.cotroller;

import toyLanguage.model.exceptions.FileException;
import toyLanguage.model.exceptions.MyException;
import toyLanguage.model.programState.*;
import toyLanguage.model.values.RefValue;
import toyLanguage.model.values.Value;
import toyLanguage.repository.IRepository;

import java.io.IOException;
import java.util.*;
import java.util.concurrent.*;
import java.util.stream.Collectors;

public class Controller {
    private IRepository repo;
    boolean displayFlag;
    private ExecutorService executor;
    public Controller(IRepository repo, String flag){
        this.repo = repo;
        //displayFlag = false;
        if(Objects.equals(flag, "1"))
            this.displayFlag = true;
        else
            this.displayFlag = false;
    }

    public Controller(IRepository repo){
        this.repo = repo;
    }

    public void setDisplayFlag(String flag) {
        if(flag.equals("1"))
            this.displayFlag = true;
        else
            this.displayFlag = false;
    }

/*    public void allStep() throws MyException, IOException {
        PrgState prg = repo.getCrtPrg();
        if(prg.getStack().isEmpty()) throw new MyException("The execution stack is empty.");
        if(displayFlag)
            System.out.println(prg);
        repo.logPrgStateExec();

        while(!prg.getStack().isEmpty()){
            oneStep(prg);
            ///repo.logPrgStateExec(); //or below?
            Map<Integer, Value> heapContent = prg.getHeap().getContent();
            //List<Integer> symbolTableAddresses = this.getAddressesFromSymTable(prg.getSymTable().getContent().values());
            //List<Integer> allReferencedAddresses = this.addIndirectAddresses(symbolTableAddresses, heapContent);

            // concurrent version:
            ConcurrentLinkedDeque<Integer> symbolTableAddresses =
                    this.getAddressesConcurrentlyFromSymTable(prg.getSymTable().getContent().values());
            ConcurrentLinkedDeque<Integer> allReferencedAddresses =
                    this.addIndirectAddressesConcurrently(symbolTableAddresses, heapContent);
            prg.getHeap().setHeap(this.garbageCollector(allReferencedAddresses, heapContent)); // garbage collector call
            repo.logPrgStateExec(); //
            if(displayFlag)
                System.out.println(prg);
        }
        System.out.println(prg);  //
    }
 */

    public void createExecutor() {
        this.executor = Executors.newFixedThreadPool(2);
    }
    public void destroyExecutor() {
        this.executor.shutdownNow();
    }
    public void oneStepForAllPrg(List<PrgState> prgList) throws InterruptedException {
        prgList.forEach(prg-> {
            try {
                repo.logPrgStateExec(prg);
                System.out.println(prg);
            } catch (FileException e) {
                throw new RuntimeException(e);
            }
        });

        // run concurrently for each thread
        // prepare callables
        List<Callable<PrgState>> callList = prgList.stream()
                .map((PrgState p)->(Callable<PrgState>)(p::oneStep)) // ()->{ return p.oneStep(); }
                .collect(Collectors.toList());   // or simply .toList()
        // start execution of callables
        // it returns the list of new created prgStates (threads)
        List<PrgState> newPrgList = executor.invokeAll(callList).stream()
                .map(future->{
                    try{
                        return future.get();
                    }
                    catch (ExecutionException | InterruptedException e) {
                        throw new RuntimeException(e);
                        //System.out.println("Runtime ERROR: ");
                        //e.printStackTrace();
                        //return null;
                    }
                })
                .filter(Objects::nonNull)   //p->p!=null
                .collect(Collectors.toList()); // or simply .toList()
        prgList.addAll(newPrgList);
        prgList.forEach(prg->{
            try {
                repo.logPrgStateExec(prg);
                System.out.println(prg);
            } catch (FileException e) {
                throw new RuntimeException(e);
            }
        });
        repo.setPrgState(prgList);
    }

    public void allSteps() throws InterruptedException {
        executor=Executors.newFixedThreadPool(2);
        // remove the completed programs
        List<PrgState> prgList = removeCompletedPrg(repo.getPrgList());
        while(prgList.size()>0){
            //garbage collector
            conservativeGarbageCollector(prgList);
            oneStepForAllPrg(prgList);
            //remove completed
            prgList = removeCompletedPrg(repo.getPrgList());
        }
        executor.shutdownNow();
        // HERE the repository still contains at least one Completed Prg
        // and its List<PrgState> is not empty. Note that oneStepForAllPrg calls the method
        // setPrgList of repository in order to change the repository

        // update the repository state
        repo.setPrgState(prgList);
    }

    public void conservativeGarbageCollector(List<PrgState> prgList) {
        Map<Integer, Value> heapContent = prgList.get(0).getHeap().getContent();
        List<Value> symbolTableValues = prgList.stream().flatMap(prg -> prg.getSymTable().getContent().values().stream()).collect(Collectors.toList());
        List<Integer> symbolTableAddresses = this.getAddressesConcurrentlyFromSymTable(symbolTableValues);
        List<Integer> allReferencedAddresses = this.addIndirectAddressesConcurrently(symbolTableAddresses, heapContent);
        prgList.get(0).getHeap().setHeap(this.garbageCollector(allReferencedAddresses, heapContent));   // garbage collector call
        // (ConcurrentLinkedDeque<Integer>)
    }

    private Map<Integer, Value> garbageCollector(List<Integer> referencedAddresses, Map<Integer, Value> heap) {
        // concurrent linked deque for thread safety
        return heap.entrySet().stream()
                .filter(e -> referencedAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    private List<Integer> getAddressesConcurrentlyFromSymTable
            (Collection<Value> symTableValues) {
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> ((RefValue) v).getAddress())
                .collect(Collectors.toList());
    }

    private List<Integer> getAddressesFromSymTable(Collection<Value> symTableValues) {
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    private List<Integer> addIndirectAddressesConcurrently
            (List<Integer> addressesFromSymbolTable, Map<Integer, Value> heap) {
        boolean change = true;
        List<Integer> newAddressList = new ArrayList<>(addressesFromSymbolTable);   //copy of list in order to add indirections

        while (change) {
            List<Integer> appendingList; //queue?
            change = false;

            appendingList = heap.entrySet().stream()
                    .filter(e -> e.getValue() instanceof RefValue)      // check if val in heap is RefValue, so it can have indirections
                    .filter(e -> newAddressList.contains(e.getKey()))   // check if address list contains ref to this
                    .map(e -> ((RefValue) e.getValue()).getAddress())   // map the reference to its address, so we can add it
                    .filter(e -> !newAddressList.contains(e))           // check if the address list already has that reference from prev elems
                    .collect(Collectors.toList());                      // collect to list
            if (!appendingList.isEmpty()) {
                // if we get here => we still have indirect references, so we have to keep checking
                change = true;
                newAddressList.addAll(appendingList);
            }
            /*heap.entrySet().parallelStream()
                    .filter(e -> e.getValue() instanceof RefValue)
                    .filter(e -> addressesFromSymbolTable.contains(e.getKey()))
                    .map(e -> ((RefValue) e.getValue()).getAddress())
                    .filter(e -> !addressesFromSymbolTable.contains(e))
                    .forEach(appendingQueue::add);

            if (!appendingQueue.isEmpty()) {
                change = true;
                addressesFromSymbolTable.addAll(appendingQueue);
            }*/
        }
        return newAddressList;
    }

    private List<Integer> addIndirectAddresses
            (List<Integer> addressesFromSymbolTable, Map<Integer, Value> heap) {
        boolean change = true;
        List<Integer> newAddressList = new ArrayList<>(addressesFromSymbolTable);   //copy of list in order to add indirections
        // we go through heapSet again and again and each time we add to the address list new indirection level
        // and new addresses which must NOT be deleted
        while (change) {
            List<Integer> appendingList;
            change = false;
            appendingList = heap.entrySet().stream()
                    .filter(e -> e.getValue() instanceof RefValue)      // check if val in heap is RefValue, so it can have indirections
                    .filter(e -> newAddressList.contains(e.getKey()))   // check if address list contains ref to this
                    .map(e -> ((RefValue) e.getValue()).getAddress())   // map the reference to its address, so we can add it
                    .filter(e -> !newAddressList.contains(e))           // check if the address list already has that reference from prev elems
                    .collect(Collectors.toList());                      // collect to list
            if (!appendingList.isEmpty()) {
                // if we get here => we still have indirect references, so we have to keep checking
                change = true;
                newAddressList.addAll(appendingList);
            }
        }
        return newAddressList;
    }

    List<PrgState> removeCompletedPrg(List<PrgState> inPrgState){
        return inPrgState.stream()
                .filter(p->p.isNotCompleted())   //PrgState::isNotCompleted
                .collect(Collectors.toList());
    }
}
