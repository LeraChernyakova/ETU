#include <iostream>

#include "model/Square_matrix.h"
#include "model/queue/Thread_safe_queue.h"
#include "model/queue/impl/Thread_safe_queue_impl.h"
#include "model/queue/impl/Thread_safe_queue_impl_fine.h"
#include "thread/Matrix_threading.h"

//#define DEBUG

void
generate_producer(std::shared_ptr<Thread_safe_queue<std::pair<Square_matrix, Square_matrix>>> gen_queue,
                  int matrix_size, std::atomic<bool> &stopFlag) {
    while (!stopFlag) {
        Matrix_threading::generate(matrix_size, gen_queue);
    }
}

void
calculate_consumer_producer(std::shared_ptr<Thread_safe_queue<std::pair<Square_matrix, Square_matrix>>> gen_queue,
                            std::shared_ptr<Thread_safe_queue<Square_matrix>> output_queue, int multi_threads_count,
                            std::atomic<bool> &stopFlag) {
    while (!stopFlag) {
        std::shared_ptr<std::pair<Square_matrix, Square_matrix>> matrices = gen_queue->wait_and_pop();
        Matrix_threading::multiply(multi_threads_count, output_queue, matrices);
    }
}

void
output_consumer(std::shared_ptr<Thread_safe_queue<Square_matrix>> output_queue, std::string_view output_path,
                std::atomic<long long> &counter, std::atomic<bool> &stopFlag) {
    while (!stopFlag) {
        std::shared_ptr<Square_matrix> matrix = output_queue->wait_and_pop();
        Matrix_threading::output(output_path, matrix);
        {
            counter++;
        }
    }
}

int main(int args, char** argv) {

#ifdef DEBUG
    bool isFine{true};
    int producer_count{100};
    int multi_threads_count{40};
    int matrix_size{40};
#else
    if (args != 5) {
        std::exit(-1);
    }

    bool isFine(std::stoi(argv[1]));
    int producer_count{std::stoi(argv[2])};
    int multi_threads_count{std::stoi(argv[3])};
    int matrix_size{std::stoi(argv[4])};
#endif

    int stop_time_mills{1000};
    std::string output_path{"output.txt"};

    std::atomic<long long> counter{0};
    std::atomic<bool> stopFlag{false};

    std::shared_ptr<Thread_safe_queue<std::pair<Square_matrix, Square_matrix>>> gen_queue;
    std::shared_ptr<Thread_safe_queue<Square_matrix>> output_queue;

    if (isFine) {
        gen_queue = std::make_shared<Thread_safe_queue_impl_fine<std::pair<Square_matrix, Square_matrix>>>();
        output_queue = std::make_shared<Thread_safe_queue_impl_fine<Square_matrix>>();
    } else {
        gen_queue = std::make_shared<Thread_safe_queue_impl<std::pair<Square_matrix, Square_matrix>>>();
        output_queue = std::make_shared<Thread_safe_queue_impl<Square_matrix>>();
    }


    std::vector<std::thread> working_thread;

    for (int i = 0; i < producer_count; ++i) {
        working_thread.emplace_back(generate_producer, gen_queue, matrix_size, std::ref(stopFlag));
        working_thread.emplace_back(calculate_consumer_producer, gen_queue, output_queue, multi_threads_count,
                                    std::ref(stopFlag));
        working_thread.emplace_back(output_consumer, output_queue, output_path, std::ref(counter), std::ref(stopFlag));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(stop_time_mills));

    stopFlag = true;

    std::cout << counter << std::endl;

    std::exit(0);

    return 0;
}
