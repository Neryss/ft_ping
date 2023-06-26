# ft_ping

Re create the `ping` command line in C (with some limitations).

## usage
`./sudo ft_ping <options> <destination>`

### Notes
You can check which option is implemented using the `-h` option, the ones marked as "TODO" are obviously not done.

Also, my parsing sucks and is held by ducktape and glue don't judge it, everything else is usable.

## Tips
- You should really use [Wireshark]("https://www.wireshark.org/") to test and see how packets are sent and why yours might not check all the requirements to get a packet back.
- Use `alarm()` as a good way to wait for x amount of seconds consistently
- Don't overthink your headers. You could do it as I deal and only deal with the ICMP header using the `struct	icmphdr` (kernel should handle the IPV4 header on its own). You can also create your own packet and handle the headers manually if you wish to do so.
- Since you cannot use any FD or socket handling, you can only wait and receive, also you cannot use `fcntl()` so use your own way of testing the socket.
- Last one: if you have issues receiving packets, **USE WIRESHARK** and check for checksum errors, if it's the case, read the universal [man]("https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol") about the checksum part.

## Known issues

- Not displaying the same amount of reiceved bytes as the mordern ping since the later one uses a timestamp field in the icmp header.
- Total exec time couldn't be done with `gettimeofday()` since the function should never be used to calculate these kind of things ([here's]("https://blog.habets.se/2010/09/gettimeofday-should-never-be-used-to-measure-time.html") a better explanation as of why).
- I'm not checking for receive specific error such as errors described in the packet sent back to you, it's not asked but I'll do it for `traceroute`.
- I don't do any reverse DNS lookup.
- I don't handle IPV6 (I used this project as an intro and aim to do a deeper work with the following project).

## The end

I hope it can help some of you out, I know it sucks being post CC without any teammates to work with and I wish you can use this repo in some way to help you find things you were struggling with or anything. Much love.