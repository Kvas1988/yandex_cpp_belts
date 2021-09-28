#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>

using namespace std;

// =====================================================
class TeamTasks {
public:
    // ѕолучить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return tasks.at(person);
    }

    // ƒобавить новую задачу (в статусе NEW) дл€ конкретного разработчитка
    void AddNewTask(const string& person) {
        ++tasks[person][TaskStatus::NEW];
    }

    TaskStatus Next(TaskStatus status) {
        return static_cast<TaskStatus>(static_cast<int>(status) + 1);
    }

    void RemoveZeroStatus(TasksInfo& tasks) {
        vector<TaskStatus> remove;
        for (const auto& i : tasks) {
            if (i.second == 0) {
                remove.push_back(i.first);
            }
        }
        for (const auto& status : remove) {
            tasks.erase(status);
        }
    }

    // ќбновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo updated, untouched;
        for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
            /*updated[static_cast<TaskStatus>(i + 1)] = min(tasks[person][static_cast<TaskStatus>(i)], task_count);
            task_count -= updated[static_cast<TaskStatus>(i + 1)];*/
            updated[Next(status)] = min(tasks[person][status], task_count);
            task_count -= updated[Next(status)];
        }

        for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
            /*if (i < 3) {
                untouched[static_cast<TaskStatus>(i)] = tasks[person][static_cast<TaskStatus>(i)] - updated[static_cast<TaskStatus>(i + 1)];
                tasks[person][static_cast<TaskStatus>(i)] -= updated[static_cast<TaskStatus>(i + 1)];
            }
            tasks[person][static_cast<TaskStatus>(i)] += updated[static_cast<TaskStatus>(i)];*/
            untouched[status] = tasks[person][status] - updated[Next(status)];
            tasks[person][status] += updated[status] - updated[Next(status)];
        }
        tasks[person][TaskStatus::DONE] += updated[TaskStatus::DONE];

        RemoveZeroStatus(updated);
        RemoveZeroStatus(untouched);
        RemoveZeroStatus(tasks[person]);

        return make_tuple(updated, untouched);
    }

private:
    map<string, TasksInfo> tasks;
};