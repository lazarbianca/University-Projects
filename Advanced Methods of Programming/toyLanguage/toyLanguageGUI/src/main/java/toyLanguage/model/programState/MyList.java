package toyLanguage.model.programState;

import java.util.LinkedList;
import java.util.List;

public class MyList<T> implements IList<T>{
    private List<T> output;
    public MyList(){
        output = new LinkedList<T>();
    }
    @Override
    public void add(T object) {
        output.add(object);
    }

    @Override
    public void clear() {
        output.clear();
    }

    public List<T> getOutput() {
        return output;
    }

    public void setOutput(List<T> output) {
        this.output = output;
    }

    @Override
    public void add(int index, T object) {

    }

    @Override
    public T get(int index) {
        return null;
    }

    @Override
    public void set(int index, T object) {

    }

    @Override
    public String toString() {
        return "MyList{" +
                "output=" + output +
                '}';
    }

    @Override
    public void remove(T object) {

    }
}
