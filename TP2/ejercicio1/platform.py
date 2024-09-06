import platform
def detect_os(os_name=None):
    os_name == platform.system()
    if os_name == 'Windows':
        return 'Windows'
    elif os_name in ['Linux', 'Darwin']:
        return 'UNIX'
    else:
        return 'unknow os'

osType = detect_os()
