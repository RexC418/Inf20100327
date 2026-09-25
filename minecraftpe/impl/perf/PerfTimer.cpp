#include <perf/PerfTimer.hpp>
#include <cpputils.hpp>


std::map<std::string, float> PerfTimer::times;
std::string PerfTimer::path = "";
std::vector<double> PerfTimer::startTimes;
std::vector<std::string> PerfTimer::paths;
bool_t PerfTimer::enabled = 0;

std::vector<PerfTimer::ResultField> PerfTimer::getLog(const std::string& a2) {
	if(PerfTimer::enabled) {
		std::string v31 = a2;
		auto&& it = PerfTimer::times.find("root");
		float v7 = it == PerfTimer::times.end() ? 0 : it->second;
		auto&& it2 = PerfTimer::times.find(v31);
		float v2 = it2 != PerfTimer::times.end() ? it2->second : -1;

		std::vector<PerfTimer::ResultField> v33;
		if(v31.size()) {
			v31 += ".";
		}
	} else {
		return {};
	}
	printf("PerfTimer::getLog - not implemented\n"); //TODO PerfTimer::getLog
	return {};
}
void PerfTimer::pop() {
	if(PerfTimer::enabled) {
		double time = getTimeS();
		PerfTimer::paths.pop_back();
		PerfTimer::startTimes.pop_back();
		float v3 = time - PerfTimer::startTimes.back();
		PerfTimer::times.insert({PerfTimer::path, v3});

		if(PerfTimer::paths.size()) {
			PerfTimer::path = PerfTimer::paths[PerfTimer::paths.size() - 1];
		} else {
			PerfTimer::path = "";
		}
	}
}
void PerfTimer::popPush(const std::string& a1) {
	PerfTimer::pop();
	PerfTimer::push(a1);
}
void PerfTimer::push(const std::string& a2) {
	if(PerfTimer::enabled) {
		if(PerfTimer::path.size()) {
			PerfTimer::path += ".";
		}
		PerfTimer::path += a2;
		PerfTimer::paths.emplace_back(PerfTimer::path);
		PerfTimer::startTimes.push_back(getTimeS());
	}

}
void PerfTimer::reset() {
	PerfTimer::times.clear();
}
