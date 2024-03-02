package toyLanguage.model.programState;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.MyException;

import java.util.Map;

public interface IHeap<E> {
    int put(E value); //returns the addr on which the value was stored
    E lookup(int address) throws ADTException;
    void remove(int address);
    void update(int address, E newValue) throws ADTException;
    boolean isDefined(int address);
    void setHeap(Map<Integer, E> newContent);
    Map<Integer, E> getContent();
}
