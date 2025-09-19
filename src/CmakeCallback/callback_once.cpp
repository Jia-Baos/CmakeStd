#include <iostream>
#include <mutex>
#include <memory>
#include <atomic>
#include <future>
#include <shared_mutex>

class Task {

public:
    Task() = default;
    ~Task() = default;
    std::string TaskImpl(std::string t_task_id);

private:
    enum class TaskStatus {
        Idle,
        Running,
        Finished
    };

    std::string m_task_id{};
    std::future<void> m_task_future{};
    std::shared_mutex m_result_mutex{};
    std::atomic<TaskStatus> m_task_status{ TaskStatus::Idle };
};

std::string Task::TaskImpl(std::string t_task_id)
{
    std::string output_string{ "none" };

    if (!m_task_id.empty() && t_task_id.find(m_task_id) != std::string::npos) { // 当前已经存在任务，且查询任务的id和当前任务的id一致
        if (m_task_status == TaskStatus::Running) {
            return "running";
        } else if (m_task_status == TaskStatus::Finished) {
            return "success or failed";
        }
    } else { // 当前不存在任务，则直接启用新的任务
        {
            std::unique_lock<std::shared_mutex> lock(m_result_mutex);
            m_task_id = t_task_id;
            m_task_status = TaskStatus::Running;
        }

        m_task_future = std::async(std::launch::async, [this, t_task_id]() {

            std::unique_lock<std::shared_mutex> lock(m_result_mutex);
            auto task_id = t_task_id;

            // ...执行识别任务...

            m_task_status = TaskStatus::Finished; });

        return "running";
    }

    return output_string;
}

int main()
{
    return 0;
}