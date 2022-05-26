// Copyright 2022 Ivanov Arkady
#include "../../../modules/task_4/ivanov_a_radix_batchers_mergesort_std/rbms.h"

int partner(int nodeIndex, int mergeStage, int mergeStageStep) {
    if (mergeStageStep > mergeStage)
        throw "ERROR";

    if (mergeStageStep == 1) {
        return nodeIndex ^ (1 << (mergeStage - 1));
    } else {
        int scale = 1 << (mergeStage - mergeStageStep);  // difference between nodes for stage n stageStep n.s
        int box = 1 << mergeStageStep;
        int sn = nodeIndex / scale - (nodeIndex / scale / box) * box;
        if (sn == 0 || sn == box - 1)
            return nodeIndex;
        else if (sn % 2 == 0)
            return nodeIndex - scale;
        else
            return nodeIndex + scale;
    }
}
