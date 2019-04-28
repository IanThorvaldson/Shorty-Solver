from flask import Flask
import pexpect
import pexpect.popen_spawn

print("Initial startup (starting C++)...")
cppProgram = pexpect.popen_spawn.PopenSpawn("./ShortySolver")
cppProgram.expect('>\n', timeout=600)
#cppProgram = None
print("Started up!")

app = Flask(__name__)

users = []
