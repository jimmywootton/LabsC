template<typename T>
class stack
{
    private:
        T data[20]; //allocated size
        int size;
        const int MAX_SIZE = 20; //max size constant int
    public:
        stack()
        {
            size = 0; //initialize stack to size 0
        }
        void push(T val)
        {
            if (size == MAX_SIZE) //when there is no space left in  stack
            {
                throw std::overflow_error("Called push on full stack."); 
            }
            data[size] = val; //add item to push
            size += 1; //increase size by one
        }
        void pop()
        {
            if (empty()) //exception for removing a item from empty stack
            {
                throw std::out_of_range("Called pop on empty stack.");
            }
            size -= 1; //decrement size
        }
        void pop_two()
        {
            if (empty()) //exception if removing two elemetns on empty stack
            {
                throw std::out_of_range("Called pop_two on empty stack.");
            }
            if (size == 1) //exception if removin two items on stack with one element
            {
                throw std::out_of_range("Called pop_two on a stack of size 1.");
            }
            size -= 2; //decrease size by two
        }
        T top()
        {
            if (empty()) //exception if there is no elements in stack
            {
                throw std::underflow_error("Called top on empty stack.");
            }
            return data[size - 1]; //returns item on top of stack
        }
        bool empty() //returns the status of if the stack is empty
        {
            return (size == 0); 
        }
};