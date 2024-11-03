package toyLanguage.model.programState;

import java.util.List;

public interface IList<T> {
    void add(T object);
    void clear();
    void add(int index, T object);
    T get(int index);
    void set(int index, T object);
    void remove(T object);
    List<T> getOutput();
}
