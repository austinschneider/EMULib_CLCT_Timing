#ifndef _jobcontrol_ProcessTree_h_
#define _jobcontrol_ProcessTree_h_

#include <map>
#include <vector>
#include <list>
#include <string>

namespace jobcontrol
{
	class ProcessTree;

	class ProcessTree
	{
		public:
			ProcessTree() {}
			~ProcessTree() {}
			void takeSnapshot();
			std::list<int> getDescendantPIDs( const int pid, int indentDepth=0 );
			std::list<int> getChildPIDs( const int pid );
			std::string getDescendantTree( const int pid, int indentDepth=0 );

		private:
			int getPPID( const std::string pid );
			std::multimap<int, int> pid_; // ppid-->pid multivalue map

	};
}
#endif
