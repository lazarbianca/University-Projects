package toyLanguage.model.programState;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.MyException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyDictionary<T,E> implements IDictionary<T,E>{
    // T == key, E == value
    private Map<T,E> map;
    public MyDictionary(){
        map = new HashMap<T,E>();
    }
    @Override
    public void put(T key, E value) {
        map.put(key,value);
    }
    @Override
    public Set<T> getKeys(){
        return map.keySet();
    }
    @Override
    public void remove(T key) {map.remove(key);}
    @Override
    public boolean isDefined(T id) {
        return map.containsKey(id);
        //return map.get(id) != null;
    }
    @Override
    public E lookup(T id) throws ADTException {
        return map.get(id);
    }
    public Map<T, E> getContent() {
        return map;
    }
    public void setMap(Map<T, E> map) {
        this.map = map;
    }
    @Override
    public void update(T id, E val) {

        map.put(id, val);
        //else throw new MyException("the variable's value cannot be updated (not declared)");
        /*for (Map.Entry<T, E> entry : map.entrySet()) {
            if (entry.getKey().equals(id)) {
                entry.setValue(val);
                return;
            }
            //else throw new MyException("the variable's value cannot be updated (not declared)");
        }
        throw new MyException("the variable's value cannot be updated (not declared)");*/
    }

    @Override
    public String toString() {
        return "MyDictionary{" +
                "map=" + map +
                '}';
    }
}
