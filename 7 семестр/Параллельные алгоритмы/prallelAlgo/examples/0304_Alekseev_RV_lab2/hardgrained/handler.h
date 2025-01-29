#ifndef HANDLER_H
#define HANDLER_H

#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>

#define MAT_Y 4
#define MAT_N 4
#define MAT_X 4

struct node
{
	int left[MAT_Y][MAT_N];
	int right[MAT_N][MAT_X];
	//node* next;
};

class Handler {
public:
	Handler();

	void push(const node& new_node);
	void pop();

	void handle(const node& this_node);

private:
	std::mutex mutex;
	std::queue<node> queue;
	std::condition_variable cv;
};

#endif