export module engine.scheduler;

#include <chrono>
#include <SDL.h>

class RPG;

export namespace engine {
	class Task {
	private:
		RPG& rpg;

		Uint32 repetitions;
		Uint32 delay;
		Uint32 initialDelay;
		std::chrono::steady_clock::time_point lastExecuted;

	protected:
		Task(RPG& rpg);

	public:
		virtual void execute() = 0;
		virtual bool shouldExecute() = 0;
		virtual bool shouldTerminate() = 0;

		void incrementRepetitions();
		void updateLastExecuted();
	};

	class TaskScheduler {
	private:
		RPG& rpg;
		std::vector<std::unique_ptr<Task>> tasks;

	public:
		TaskScheduler(RPG& rpg);

		template <typename T, typename... Args>
		void schedule(Args&&... args);
		void onTick();
	};
}