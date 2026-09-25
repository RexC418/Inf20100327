#pragma once
#include <util/Util.hpp>
#include <string>
#include <vector>
#include <map>

struct PerfTimer
{
	struct ResultField
	{
		float field_0;
		float field_4;
		std::string field_8;

		ResultField(PerfTimer::ResultField&& a2) {
			this->field_0 = a2.field_0;
			this->field_8 = a2.field_8;
			a2.field_8 = "";
		}
		ResultField(const PerfTimer::ResultField& a2) {
			this->field_0 = a2.field_0;
			this->field_4 = a2.field_4;
			this->field_8 = a2.field_8;
		}

		int32_t getColor() const {
			return (Util::hashCode(this->field_8) & 0xAAAAAA) + 4473924;
		}
		bool_t operator <(const PerfTimer::ResultField& a2) const {
			if (this->field_0 == a2.field_0) {
				return this->field_8.compare(a2.field_8);
			}
			return this->field_0 > a2.field_0;
		}

		PerfTimer::ResultField& operator =(PerfTimer::ResultField&& a2) {
			this->field_0 = a2.field_0;
			this->field_4 = a2.field_4;
			this->field_8 = a2.field_8;
			return *this;
		}
		~ResultField() {
		}
	};

	static std::map<std::string, float> times;
	static std::string path;
	static std::vector<double> startTimes;
	static std::vector<std::string> paths;
	static bool_t enabled;


	static std::vector<PerfTimer::ResultField> getLog(const std::string&);
	static void pop();
	static void popPush(const std::string&);
	static void push(const std::string&);
	static void reset();
};
