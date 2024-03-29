#ifndef GAP_FINDER_H
#define GAP_FINDER_H

#include <ros/ros.h>
#include <vector>
#include <sensor_msgs/LaserScan.h>
#include <dynamic_gap/gap.h>
#include <boost/shared_ptr.hpp>
#include <dynamic_gap/dynamicgap_config.h>

namespace dynamic_gap {
    class GapUtils 
    {
        public: 
        GapUtils();

        ~GapUtils();

        GapUtils(const DynamicGapConfig& cfg);

        GapUtils& operator=(GapUtils other) {cfg_ = other.cfg_;};

        GapUtils(const GapUtils &t) {cfg_ = t.cfg_;};

        void hybridScanGap(boost::shared_ptr<sensor_msgs::LaserScan const>, std::vector<dynamic_gap::Gap>&);

        void mergeGapsOneGo(boost::shared_ptr<sensor_msgs::LaserScan const>,
        std::vector<dynamic_gap::Gap>&);

        void setMergeThreshold(float);
        void setIdxThreshold(int);


        private:
            const DynamicGapConfig* cfg_;

    };


}


#endif