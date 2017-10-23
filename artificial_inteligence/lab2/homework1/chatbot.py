import random
from time import sleep

import aiml
import os
import pickle
import sys

import select

from Peer import Peer

CUSTOM_SESSION_ID = "_global"

def load_kernel_memory(kernel, memoised_peer):
    kernel.setPredicate("name", memoised_peer.name)
    kernel.setPredicate("age", memoised_peer.age)
    kernel.setPredicate("job", memoised_peer.job)
    for key, val in memoised_peer.custom_props.iteritems():
        kernel.setPredicate(key, val)


def get_memoised_peer(memory, name):
    for peer in memory:
        if peer.name == name:
            return peer

    return None

def set_default_predicates(kernel):
    kernel.setPredicate("prog_normal_1-a", "false")
    kernel.setPredicate("prog_normal_2-a", "false")
    kernel.setPredicate("prog_normal_3-a", "false")
    kernel.setPredicate("prog_normal_4-a", "false")
    kernel.setPredicate("prog_normal_5-a", "false")

    kernel.setPredicate("prog_bat_1-a", "false")
    kernel.setPredicate("prog_bat_2-a", "false")
    kernel.setPredicate("prog_bat_3-a", "false")
    kernel.setPredicate("prog_bat_4-a", "false")
    kernel.setPredicate("prog_bat_5-a", "false")

    kernel.setPredicate("prof_normal_1-a", "false")
    kernel.setPredicate("prof_normal_2-a", "false")
    kernel.setPredicate("prof_normal_3-a", "false")
    kernel.setPredicate("prof_normal_4-a", "false")
    kernel.setPredicate("prof_normal_5-a", "false")

    kernel.setPredicate("prof_bat_1-a", "false")
    kernel.setPredicate("prof_bat_2-a", "false")
    kernel.setPredicate("prof_bat_3-a", "false")
    kernel.setPredicate("prof_bat_4-a", "false")
    kernel.setPredicate("prof_bat_5-a", "false")

    kernel.setPredicate("stud_normal_1-a", "false")
    kernel.setPredicate("stud_normal_2-a", "false")
    kernel.setPredicate("stud_normal_3-a", "false")
    kernel.setPredicate("stud_normal_4-a", "false")
    kernel.setPredicate("stud_normal_5-a", "false")

    kernel.setPredicate("stud_bat_1-a", "false")
    kernel.setPredicate("stud_bat_2-a", "false")
    kernel.setPredicate("stud_bat_3-a", "false")
    kernel.setPredicate("stud_bat_4-a", "false")
    kernel.setPredicate("stud_bat_5-a", "false")

    kernel.setPredicate("elev_tan_1-a", "false")
    kernel.setPredicate("elev_tan_2-a", "false")
    kernel.setPredicate("elev_tan_3-a", "false")
    kernel.setPredicate("elev_tan_4-a", "false")
    kernel.setPredicate("elev_tan_5-a", "false")

def main():

    memory = []
    storage_location = "/home/cristi/fii2/ai/storage"
    if os.path.exists(storage_location):
        memory = pickle.load(open(storage_location))

    # multiple user support
    while True:

        job = None
        age = None
        age_label = None

        name = raw_input("Cine esti?: ")

        for item in name.split():
            if item.lower() != item and item not in ['Sunt', 'Ma']:
                name = item
                break
        memoised_peer = get_memoised_peer(memory, name)

        if memoised_peer is None:
            # integrate in the GUI
            job = raw_input("Cu ce te ocupi?: ")
            job = job.split()[-1]
            age = raw_input("Cati ani ai?: ")
            for item in age.split():
                try:
                    age = int(item)
                except:
                    continue

            memoised_peer = Peer(age, job, name)
            memory.append(memoised_peer)

            if memoised_peer.age < 18:
                memoised_peer.age_label = "tanar"
            elif memoised_peer.age < 30:
                memoised_peer.age_label = "normal"
            else:
                memoised_peer.age_label = "batran"
        else:
            job = memoised_peer.job
            age = int(memoised_peer.age)

            # integrate in the GUI
            print "Welcome back, %s" % name

        age_label = memoised_peer.age_label

        kernel = aiml.Kernel()
        # kernel.loadBrain("bot_brain.brn")
        kernel.learn("/home/cristi/fii2/ai/std-startup.xml")
        kernel.respond("load aiml b")

        # optimize to be dynamically
        kernel.setPredicate("name", name)
        kernel.setPredicate("job", job)
        kernel.setPredicate("age", age)
        kernel.setPredicate("age_label", age_label)

        kernel.respond("load aiml c")

        set_default_predicates(kernel)

        flag = random.randint(3, 5)
        # flag = 5
        loop_counter = 0
        question_mode = True
        while True:
            loop_counter += 1
            if question_mode:
                bot_response = ""
                while bot_response == "":
                    bot_response = kernel.respond("intrebari")
                print bot_response

            i, o, e = select.select([sys.stdin], [], [], 30)

            if (i):
                peer_input = raw_input(">>> ")
            else:
                print 'Zi si tu ceva!'
                continue

            if peer_input == 'quit':
                print "O zi buna!"
                memoised_peer.custom_props = kernel.getSessionData(CUSTOM_SESSION_ID)
                pickle.dump(memory, open(storage_location, "w"))
                # serialize dynamically set properties
                os._exit(1)
            elif peer_input == 'buzz':
                loop_counter = flag

            print kernel.respond(peer_input)
            sleep(1)

            if loop_counter == flag:
                kernel = aiml.Kernel()
                kernel.learn("/home/cristi/fii2/ai/contextual-start-up.xml")
                kernel.respond("load aiml c")
                memoised_peer.custom_props = kernel.getSessionData(CUSTOM_SESSION_ID)
                memoised_peer.age = str(memoised_peer.age)
                load_kernel_memory(kernel, memoised_peer)
                print "Te-am intrebat destule, mai zi si tu ceva!"
                question_mode = False

main()