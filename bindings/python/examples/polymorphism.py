#!/usr/bin/python

import storage


device_graph = storage.DeviceGraph()

sda = storage.Disk.create(device_graph, "/dev/sda")

gpt = sda.createPartitionTable("gpt")

sda1 = gpt.createPartition("/dev/sda1")
sda2 = gpt.createPartition("/dev/sda2")

device_graph.print_graph()


print "partitions on gpt:"
for partition in gpt.getPartitions():
  print "  %s %s" % (partition.display_name(), partition.getNumber())
print


print "descendants of sda:"
for device in sda.getDescendants(False):

  partition_table = storage.CastToPartitionTable(device)
  if partition_table:
    print "  %s is partition table" % partition_table.display_name()
    
  partition = storage.CastToPartition(device)
  if partition:
    print "  %s %s is partition" % (partition.display_name(), partition.getNumber())

print