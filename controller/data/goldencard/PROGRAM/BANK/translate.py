import os
import struct

def riff_unpack(data):
  ptr = 12
  riff = []
  while ptr < len(data):
    tag_name = data[ptr:ptr + 4]
    ptr += 4
    size = struct.unpack('<i', data[ptr:ptr + 4])[0]
    ptr += 4
    riff.append((tag_name, size, data[ptr:ptr + size]))
    ptr += size
  return riff

def riff_pack(riff):
  bytes = []
  for tag, size, data in riff:
    bytes.append(tag)
    bytes.append(struct.pack('<i', size))
    bytes.append(data)
  return ''.join(bytes)


for root, dirs, files in os.walk('.'):
  for f in files:
    if f.endswith('.PRO'):
      data = file(os.path.join(root, f), 'rb').read()
      patch_data = riff_unpack(data)
      tag, size, partdata = patch_data[2]
      partdata = list(partdata)
      if partdata[9 + 4] == '\x00':
        partdata[9 + 4] = '\x01'
      patch_data[2] = tag, size, ''.join(partdata)
      data = data[:12] + riff_pack(patch_data)
      file(os.path.join(root, f), 'wb').write(data)