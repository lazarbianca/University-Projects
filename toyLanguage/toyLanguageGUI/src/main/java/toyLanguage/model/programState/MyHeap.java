package toyLanguage.model.programState;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.MyException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

public class MyHeap<E> implements IHeap<E>{
    private ConcurrentHashMap<Integer, E> map;
    //HashMap<Integer,E> map;
    private int address=0; //null address for HEAP; start from 1
    // static ?.
    public MyHeap() {
        address = 0;
        map = new ConcurrentHashMap<Integer,E>();
    }
    @Override
    public int put(E value) {
        address++;
        map.put(address,value);
        return address;
    }

    @Override
    public E lookup(int address) throws ADTException {
        return map.get(address);
    }

    @Override
    public void remove(int address) {
        map.remove(address);
    }

    @Override
    public void update(int address, E newValue) throws ADTException {
        map.put(address, newValue);
    }

    @Override
    public boolean isDefined(int address) {
        return map.containsKey(address);
    }

    @Override
    public void setHeap(Map<Integer, E> newContent) {
        this.map.clear();
        this.map.putAll(newContent);
    }

    @Override
    public Map<Integer, E> getContent() {
        return map;
    }

//    @Override
//    public String toString() {
//        return "MyHeap{" +
//                "map=" + map +
//                '}';
//    }
    @Override
    public String toString() {
        StringBuilder elemsInString = new StringBuilder("{");
        int i = 0;
        for (Map.Entry<Integer, E> entry: this.map.entrySet()) {
            int key = entry.getKey();
            E value = entry.getValue();
            elemsInString.append(key);
            elemsInString.append(" -> ");
            elemsInString.append(value.toString());
            if (i < this.map.size() - 1) {
                elemsInString.append(", ");
            }
            i += 1;
        }
        elemsInString.append("}");
        return elemsInString.toString();
    }
}


/*
public class MyHeapTable extends MyDictionary<Integer, Value>{
    private int lastAddr;

    public MyHeapTable() {
        this.lastAddr = 0;
    }

    public int getLastAddr()
    {
        return this.lastAddr;
    }

    public void goToNextAddr()
    {
        this.lastAddr += 1;
    }

    public int allocateNewAddr()
    {
        this.lastAddr += 1;
        return this.lastAddr;
    }

//    public void setContent(Map<Integer, Value> map){
//        this.dictionary = map;
//    }
//
//    public Map<Integer,Value> getContent(){
//        return this.dictionary;
//    }

 */
