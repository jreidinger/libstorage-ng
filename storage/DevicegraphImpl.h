#ifndef DEVICE_GRAPH_IMPL_H
#define DEVICE_GRAPH_IMPL_H


#include <boost/noncopyable.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "storage/Devices/Device.h"
#include "storage/Devices/BlkDevice.h"
#include "storage/Holders/Holder.h"
#include "storage/Devicegraph.h"


namespace storage_bgl
{

    class Devicegraph::Impl : private boost::noncopyable
    {

    public:

	// Using OutEdgeList=boost::setS disallowes parallel edges.  Using
	// VertexList=boost::listS makes iterators stable.  See:
	// http://www.boost.org/doc/libs/1_56_0/libs/graph/doc/adjacency_list.html

	// The shared_ptr is required for runtime polymorphism of Device and
	// Holder.  Using newer bundled properties instead of cumbersome internal
	// properties, see:
	// http://www.boost.org/doc/libs/1_56_0/libs/graph/doc/bundles.html

	typedef boost::adjacency_list<boost::setS, boost::listS, boost::bidirectionalS,
				      shared_ptr<Device>, shared_ptr<Holder>> graph_t;

	typedef graph_t::vertex_descriptor vertex_descriptor;
	typedef graph_t::edge_descriptor edge_descriptor;

	typedef graph_t::vertex_iterator vertex_iterator;
	typedef graph_t::edge_iterator edge_iterator;

	typedef graph_t::vertices_size_type vertices_size_type;

	bool empty() const;

	size_t num_devices() const;
	size_t num_holders() const;

	set<sid_t> get_sids() const;

	vertex_descriptor find_vertex(sid_t sid) const;

	void remove_vertex(vertex_descriptor a);

	boost::iterator_range<vertex_iterator> vertices() const;
	boost::iterator_range<edge_iterator> edges() const;

	void load(Devicegraph* devicegraph, const string& filename);
	void save(const string& filename) const;

	void print_graph() const;
	void write_graphviz(const string& filename) const;

	size_t num_children(vertex_descriptor vertex) const;
	size_t num_parents(vertex_descriptor vertex) const;

	vertex_descriptor child(vertex_descriptor vertex) const;
	vertex_descriptor parent(vertex_descriptor vertex) const;

	vector<vertex_descriptor> children(vertex_descriptor vertex) const;
	vector<vertex_descriptor> parents(vertex_descriptor vertex) const;
	vector<vertex_descriptor> siblings(vertex_descriptor vertex, bool itself) const;
	vector<vertex_descriptor> descendants(vertex_descriptor vertex, bool itself) const;
	vector<vertex_descriptor> ancestors(vertex_descriptor vertex, bool itself) const;
	vector<vertex_descriptor> leafs(vertex_descriptor vertex, bool itself) const;
	vector<vertex_descriptor> roots(vertex_descriptor vertex, bool itself) const;

	template <typename Type>
	vector<const Type*>
	getDevices(const vector<vertex_descriptor>& vertices) const // TODO rename
	{
	    vector<const Type*> ret;

	    for (vertex_descriptor vertex : vertices)
	    {
		const Type* device = dynamic_cast<const Type*>(graph[vertex].get());
		if (!device)
		    throw bad_cast();

		ret.push_back(device);
	    }

	    return ret;
	}

	template <typename Type, typename Predicate>
	vector<Type*>
	getDevicesIf(Predicate pred) const // TODO rename
	{
	    vector<Type*> ret;

	    for (vertex_descriptor vertex : vertices())
	    {
		Type* device = dynamic_cast<Type*>(graph[vertex].get());
		if (device && pred(device))
		    ret.push_back(device);
	    }

	    return ret;
	}

	void swap(Devicegraph::Impl& x);

	graph_t graph;

    };

}

#endif
