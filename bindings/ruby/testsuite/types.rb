#!/usr/bin/ruby

require 'test/unit'
require 'storage'


class TestTypes < Test::Unit::TestCase

  def test_types

    devicegraph = Storage::Devicegraph.new()
    sda = Storage::Disk.create(devicegraph, "/dev/sda")
    gpt = sda.create_partition_table(Storage::GPT)
    sda1 = gpt.create_partition("/dev/sda")
    ext4 = sda1.create_filesystem(Storage::EXT4)

    assert_equal(devicegraph.empty?, false)
    assert_equal(devicegraph.num_devices, 4)

    sda.size_k = 2**64 - 1
    assert_equal(sda.size_k, 2**64 - 1)

    ext4.label = "test-label"
    assert_equal(ext4.label, "test-label")

  end

end