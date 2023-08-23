import sys, os

def bytesToU32(buf, offset, isLE):
    num = 0
    for i in range(4):
        num <<= 8
        if isLE:
            num += buf[offset + 3 - i]
        else:
            num += buf[offset + i]
    return num

def u32ToBytes(buf, offset, val, isLE):
    for i in range(4):
        if isLE:
            buf[offset + i] = (val >> (i * 8)) & 0xFF
        else:
            buf[offset + i] = (val >> ((3 - i) * 8)) & 0xFF

def fileToBytes(fileName):
    f = open(fileName, 'rb')
    dest = f.read()
    f.close()
    return dest

def bytesToFile(buf, fileName):
    try:
        os.makedirs(os.path.dirname(fileName), exist_ok=True)
    except FileNotFoundError:
        pass
    except Exception:
        return False
    try:
        f = open(fileName, 'wb')
        f.write(buf)
        f.close()
    except Exception:
        return False
    return True

if __name__=="__main__":
    if len(sys.argv) > 3:
        sys.exit()
    baseBin = bytearray(fileToBytes(os.path.dirname(__file__) + "/template/lecode-JAP.bin"))[0:0x40]
    outPutBin = baseBin + fileToBytes(sys.argv[1])
    u32ToBytes(outPutBin, 0x14, len(outPutBin), False)
    bytesToFile(outPutBin, sys.argv[2])