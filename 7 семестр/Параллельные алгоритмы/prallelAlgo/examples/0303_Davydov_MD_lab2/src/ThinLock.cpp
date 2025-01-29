#include "ThinLock.h"

ThinLock::ThinLock():head(new node),tail(head.get())
{

}

Matrix ThinLock::consume()
{ 
    std::unique_ptr<node> old_head=pop_head(); 
    return Matrix(*old_head->data.get());
}

void ThinLock::produce(Matrix new_value)
{ 
    std::shared_ptr<Matrix> new_data(
    std::make_shared<Matrix>(std::move(new_value))); 
    std::unique_ptr<node> p(new node);
    node* const new_tail=p.get(); 
    std::lock_guard<std::mutex> tail_lock(tail_mutex);
    tail->data=new_data; 
    tail->next=std::move(p);
    tail=new_tail;
    isEmpty.notify_one(); 
}
