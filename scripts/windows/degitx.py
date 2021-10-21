import subprocess

def cmd(command, out=False):
    if out:
        return subprocess.call(command, shell=True)
    else:
        return subprocess.call(command, stdout=subprocess.DEVNULL, shell=True)
def exe(command):
    return subprocess.check_output(command, shell=True, encoding='utf8')