from time import sleep
import paho.mqtt.client as mqtt

broker = 'broker.emqx.io'

forwards_topic = 'buda/leds/forwards'
backwards_topic = 'buda/leds/backwards'
leds_topic = 'buda/leds/'

prev_forwards = -1
prev_backwards = -1
cur_forwards = -1
cur_backwards = -1

max_dist=210
number_of_leds=6

def light_it_up(dist, backwards, number_of_leds, max_dist):
    n = round(dist/(max_dist/(number_of_leds+1)))
    if backwards: return number_of_leds-n+1
    return n

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("$SYS/#")

def on_message(client, userdata, msg):
    global forwards_topic
    global backwards_topic
    global prev_forwards
    global prev_backwards
    global max_dist
    global number_of_leds

    print(msg.topic+" "+str(msg.payload))
    dist = float(msg.payload)
    if str(msg.topic) == forwards_topic:
        led = light_it_up(dist, False, number_of_leds, max_dist)
        client.publish(leds_topic+str(led), '100255100')
        if led != prev_forwards:
            client.publish(leds_topic+str(prev_forwards), '000000000')
        prev_forwards = led
    if str(msg.topic) == backwards_topic:
        led = light_it_up(dist, False, number_of_leds, max_dist)
        client.publish(leds_topic+str(led), '100255100')
        if led != prev_backwards:
            client.publish(leds_topic+str(prev_backwards), '000000000')
        prev_backwards = led

client = mqtt.Client('buda')
client.on_connect = on_connect
client.on_message = on_message

client.connect(broker)
client.loop_start()
client.subscribe(forwards_topic)
client.subscribe(backwards_topic)

client.loop_forever()
