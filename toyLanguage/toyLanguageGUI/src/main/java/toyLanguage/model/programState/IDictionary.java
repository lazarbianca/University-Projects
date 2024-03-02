package toyLanguage.model.programState;

import toyLanguage.model.exceptions.ADTException;
import toyLanguage.model.exceptions.MyException;

import java.util.Map;
import java.util.Set;

public interface IDictionary<T,E> {
    void put(T key, E value);
    void remove(T key);
    public Set<T> getKeys();

    boolean isDefined(T id);

    E lookup(T id) throws ADTException;
    Map<T, E> getContent();

    void update(T id, E val) throws ADTException;
    // keySet(): (Hash)Set <T> (OR)TreeSet
    // values(): Collection<E>
}
