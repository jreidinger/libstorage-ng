
// Background is provided at http://nickdarnell.com/swig-casting-revisited/
// and https://github.com/swig/swig/blob/master/Lib/typemaps/factory.swg.

// In most cases the downcast is not required since polymorphism is handled in
// C++. But if you e.g. extend the Device classes in Ruby it is required.

// Order of classes is crucial: The first one wins so the most derived class
// must be first, e.g. Luks before Encryption. Abstract classes should not be
// listed.

%include "factory.i"

// TODO don't repeat list of types, maybe possible with %define.

%factory(storage::Device* storage::downcast, storage::Disk, storage::Md, storage::Partition,
	 storage::Gpt, storage::LvmPv, storage::LvmVg, storage::LvmLv, storage::Luks,
	 storage::Encryption, storage::Msdos, storage::Btrfs, storage::Ext4, storage::Ntfs,
	 storage::Swap, storage::Vfat, storage::Xfs, storage::Bcache, storage::BcacheCset);

%factory(const storage::Device* storage::downcast, const storage::Disk, const storage::Md,
	 const storage::Partition, const storage::Gpt, const storage::LvmPv, const storage::LvmVg,
	 const storage::LvmLv, const storage::Luks, const storage::Encryption, const storage::Msdos,
	 const storage::Btrfs, const storage::Ext4, const storage::Ntfs, const storage::Swap,
	 const storage::Vfat, const storage::Xfs, const storage::Bcache,
	 const storage::BcacheCset);

%inline %{

    namespace storage
    {

	storage::Device*
	downcast(storage::Device* device)
	{
	    return device;
	}

	const storage::Device*
	downcast(const storage::Device* device)
	{
	    return device;
	}

    }

%}
