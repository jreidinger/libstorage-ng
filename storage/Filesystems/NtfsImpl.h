/*
 * Copyright (c) 2015 Novell, Inc.
 * Copyright (c) 2016 SUSE LLC
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#ifndef STORAGE_NTFS_IMPL_H
#define STORAGE_NTFS_IMPL_H


#include "storage/Filesystems/Ntfs.h"
#include "storage/Filesystems/FilesystemImpl.h"


namespace storage
{

    using namespace std;


    template <> struct DeviceTraits<Ntfs> { static const char* classname; };


    class Ntfs::Impl : public Filesystem::Impl
    {
    public:

	Impl()
	    : Filesystem::Impl() {}

	Impl(const xmlNode* node);

	virtual FsType get_type() const override { return FsType::NTFS; }

	virtual const char* get_classname() const override { return DeviceTraits<Ntfs>::classname; }

	virtual string get_displayname() const override { return "ntfs"; }

	virtual Impl* clone() const override { return new Impl(*this); }

	virtual ResizeInfo detect_resize_info_pure() const override;

	virtual ContentInfo detect_content_info_pure() const override;

	virtual void do_create() const override;

	virtual void do_set_label() const override;

	virtual void do_resize(ResizeMode resize_mode) const override;

    };

}

#endif
