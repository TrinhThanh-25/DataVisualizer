#pragma once

#include <string>

const std::string KruskalCode = {
    "sort the edge by its weight\n"

    "for(int i = 0; i < edges.size(); i++){\n"
    "    if adding e = edgelist[i] does not form a cycle\n"
    "           add it\n"
    "    else ignore it\n"
};

const std::string PrimCode = {
    "T = {s}\n"
    "enqueue edges connected to s in PQ (by inc weight)\n"
    "while (!PQ.isEmpty)\n"
    "if (vertex v linked with e = PQ.remove ∉ T)\n"
    "    T = T ∪ {v, e}, enqueue edges connected to v\n"
    "else ignore e\n"
};