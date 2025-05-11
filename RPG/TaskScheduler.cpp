import engine.scheduler;

namespace engine {
	void Task::incrementRepetitions()
	{
		repetitions++;
	}

	void Task::updateLastExecuted()
	{
		lastExecuted = std::chrono::steady_clock::now();
	}

	Task::Task(RPG& rpg) : rpg(rpg) {}

	TaskScheduler::TaskScheduler(RPG& rpg) : rpg(rpg) {}

	void TaskScheduler::onTick()
	{
		for (auto it = tasks.begin(); it != tasks.end(); )
		{
			Task* task = (*it).get();

			if (!task->shouldExecute())
			{
				++it;
				continue;
			}

			task->execute();
			task->incrementRepetitions();
			task->updateLastExecuted();

			it = task->shouldTerminate() ? tasks.erase(it) : ++it;
		}
	}

	template <typename T, typename... Args>
	void TaskScheduler::schedule(Args&&... args)
	{
		static_assert(std::is_base_of<Task, T>::value, "T must derive from Task");
		tasks.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
}