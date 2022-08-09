#!/bin/env python3
import hid, asyncio, sys, math

# [ command, action, index, r, g, b ]
def tobyte(data):
    if type(data) is bytes:
        return data
    else:
        return (data).to_bytes(1, 'big')

def tobytes(data):
    out = b''
    for num in data:
        out += tobyte(num)
    return out

def pad_message(payload):
    return payload + b'\x00' * (32 - len(payload))

def hsv_to_rgb(h, s, v):
    h /= 360
    s /= 100
    v /= 100
    i = math.floor(h*6)
    f = h*6 - i
    p = v * (1-s)
    q = v * (1-f*s)
    t = v * (1-(1-f)*s)

    r, g, b = [
        (v, t, p),
        (q, v, p),
        (p, v, t),
        (p, q, v),
        (t, p, v),
        (v, p, q),
    ][int(i%6)]

    r, g, b = int(r * 255), int(g * 255), int(b * 255)

    return r.to_bytes(1, 'big') + g.to_bytes(1, 'big') + b.to_bytes(1, 'big')

async def set_color(device, index, c, sleep):
    # newcolor = tobytes([b'\x04', b'\x02', index, b'\xFF', b'\x00', b'\x00'])
    newcolor = b'\x04\x02\x00\x00\xFF\xFF'
    device.write(newcolor)
    await asyncio.sleep(sleep)
    # purple = tobytes([b'\x04', b'\x02', b'\x00', b'\x7A', b'\x00', b'\xFF'])
    purple = b'\x04\x02\x00\xBF\xFF\xFF'
    # purple = b'\x04\x00\xFF\x00\x00\x00' # Last State
    # purple = b'\x04\x03\x01\x7A\x00\xFF' # One Row
    device.write(purple) # set all purple

def init():
    vid = int.from_bytes(b'\x46\x53', 'big')
    pid = int.from_bytes(b'\x4D\x4D', 'big')
    usage_page = int.from_bytes(b'\xFF\x60', 'big')
    usage_id = int.from_bytes(b'\x61', 'big')
    # manufacture_string = 'foostan'
    # product_string = 'Corne'
    
    # print(vid, pid, usage_page, usage_id)
    
    device = None
    devices = hid.enumerate()
    for d in devices:
        if d['vendor_id'] == vid and d['product_id'] == pid and d['usage_page'] == usage_page and d['usage'] == usage_id:
            m_name = d["manufacturer_string"]
            d_name = d["product_string"]
            print(f"Device Found: {m_name} - {d_name}")
            device = hid.Device(path=d['path'])
            break
    if device is None:
        print("[!!] Keyboard not found, quitting.")
        exit(1)
    print("Keyboard Found")
    asyncio.run(set_color(device, b'\x00', [int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3])], 2))

init()
