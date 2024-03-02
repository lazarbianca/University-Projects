package toyLanguage.model.programState;   // in class it was called ADT

import java.util.List;
import java.util.Stack;

public interface IStack<T> {
    void push(T value);
    T pop();
    boolean isEmpty();
    List<T> getReversed();
    Stack<T> getStack();
}
