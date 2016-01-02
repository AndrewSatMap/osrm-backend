/*

Copyright (c) 2015, Project OSRM contributors
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef DATAFACADE_BASE_HPP
#define DATAFACADE_BASE_HPP

// Exposes all data access interfaces to the algorithms via base class ptr

#include "extractor/edge_based_node.hpp"
#include "extractor/external_memory_node.hpp"
#include "engine/phantom_node.hpp"
#include "extractor/turn_instructions.hpp"
#include "util/integer_range.hpp"
#include "util/osrm_exception.hpp"
#include "util/string_util.hpp"
#include "util/typedefs.hpp"

#include "osrm/coordinate.hpp"

#include <string>
#include <boost/optional.hpp>

using EdgeRange = osrm::range<EdgeID>;

template <class EdgeDataT> class BaseDataFacade
{
  public:
    using RTreeLeaf = EdgeBasedNode;
    using EdgeData = EdgeDataT;
    BaseDataFacade() {}
    virtual ~BaseDataFacade() {}

    // search graph access
    virtual unsigned GetNumberOfNodes() const = 0;

    virtual unsigned GetNumberOfEdges() const = 0;

    virtual unsigned GetOutDegree(const NodeID n) const = 0;

    virtual NodeID GetTarget(const EdgeID e) const = 0;

    virtual const EdgeDataT &GetEdgeData(const EdgeID e) const = 0;

    virtual EdgeID BeginEdges(const NodeID n) const = 0;

    virtual EdgeID EndEdges(const NodeID n) const = 0;

    virtual EdgeRange GetAdjacentEdgeRange(const NodeID node) const = 0;

    // searches for a specific edge
    virtual EdgeID FindEdge(const NodeID from, const NodeID to) const = 0;

    virtual EdgeID FindEdgeInEitherDirection(const NodeID from, const NodeID to) const = 0;

    virtual EdgeID
    FindEdgeIndicateIfReverse(const NodeID from, const NodeID to, bool &result) const = 0;

    // node and edge information access
    virtual FixedPointCoordinate GetCoordinateOfNode(const unsigned id) const = 0;

    virtual bool EdgeIsCompressed(const unsigned id) const = 0;

    virtual unsigned GetGeometryIndexForEdgeID(const unsigned id) const = 0;

    virtual void GetUncompressedGeometry(const unsigned id,
                                         std::vector<unsigned> &result_nodes) const = 0;

    virtual TurnInstruction GetTurnInstructionForEdgeID(const unsigned id) const = 0;

    virtual TravelMode GetTravelModeForEdgeID(const unsigned id) const = 0;

    virtual std::vector<PhantomNodeWithDistance>
    NearestPhantomNodesInRange(const FixedPointCoordinate &input_coordinate,
                               const float max_distance,
                               const int bearing = 0,
                               const int bearing_range = 180) = 0;

    virtual std::vector<PhantomNodeWithDistance>
    NearestPhantomNodes(const FixedPointCoordinate &input_coordinate,
                        const unsigned max_results,
                        const int bearing = 0,
                        const int bearing_range = 180) = 0;

    virtual std::pair<PhantomNode, PhantomNode>
    NearestPhantomNodeWithAlternativeFromBigComponent(const FixedPointCoordinate &input_coordinate,
                                                      const int bearing = 0,
                                                      const int bearing_range = 180) = 0;

    virtual unsigned GetCheckSum() const = 0;

    virtual bool IsCoreNode(const NodeID id) const = 0;

    virtual unsigned GetNameIndexFromEdgeID(const unsigned id) const = 0;

    virtual std::string get_name_for_id(const unsigned name_id) const = 0;

    virtual std::size_t GetCoreSize() const = 0;

    virtual std::string GetTimestamp() const = 0;
};

#endif // DATAFACADE_BASE_HPP
