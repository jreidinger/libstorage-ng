#ifndef STORAGE_H
#define STORAGE_H


#include <string>
#include <vector>
#include <list>
#include <memory>
#include <boost/noncopyable.hpp>


namespace storage
{

    class Environment;
    class Devicegraph;


    class CommitCallbacks
    {
    public:

	virtual ~CommitCallbacks() {}

	virtual void message(const std::string& message) const = 0;
	virtual bool error(const std::string& message) const = 0;

    };


    class Storage : private boost::noncopyable
    {
    public:

	Storage(const Environment& environment);
	~Storage();

    public:

	const Environment& get_environment() const;

	Devicegraph* create_devicegraph(const std::string& name);
	Devicegraph* copy_devicegraph(const std::string& source_name, const std::string& dest_name);
	void remove_devicegraph(const std::string& name);
	void restore_devicegraph(const std::string& name);

	bool equal_devicegraph(const std::string& lhs, const std::string& rhs) const;

	bool exist_devicegraph(const std::string& name) const;
	std::vector<std::string> get_devicegraph_names() const;

	Devicegraph* get_devicegraph(const std::string& name);
	const Devicegraph* get_devicegraph(const std::string& name) const;

	Devicegraph* get_current();
	const Devicegraph* get_current() const;

	const Devicegraph* get_probed() const;

	const std::string& get_rootprefix() const;
	void set_rootprefix(const std::string& rootprefix);

	std::list<std::string> get_commit_steps() const;
	void commit(const CommitCallbacks* commit_callbacks = nullptr);

    public:

	class Impl;

	Impl& get_impl() { return *impl; }
	const Impl& get_impl() const { return *impl; }

    private:

	std::shared_ptr<Impl> impl;

    };

}

#endif
