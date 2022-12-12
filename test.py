import subprocess

# define the command and the arguments for turning off a monitor
command = "clickmonitorddc"
args = ["-monitor", "1", "-off"]

# call the command using the `subprocess.run()` method
result = subprocess.run([command] + args)

# check the return code to see if the command was successful
if result.returncode == 0:
    print("Monitor was turned off successfully")
else:
    print("There was an error turning off the monitor")
