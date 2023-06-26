# ft_ping

re create ping in c

## usage
`./sudo ft_ping <options> <destination>`

## Tips
- You should really use [Wireshark]("https://www.wireshark.org/") to test and see how packets are sent and why yours might not check all the requirements to get a packet back
- Use `alarm()` as a good way to wait for x amount of seconds consistently
- Don't overthink your headers. You could do it as I deal and only deal with the ICMP header using the `struct	icmphdr` (kernel should handle the IPV4 header on its own). You can also create your own packet and handle the headers manually if you wish to do so
- 

## Known issues

- Not displaying the same amount of reiceved bytes as the mordern ping since the later one uses a timestamp field in the icmp header
- Total exec time couldn't be done with `gettimeofday()` since the function should never be used to calculate these kind of things ([here's]("https://blog.habets.se/2010/09/gettimeofday-should-never-be-used-to-measure-time.html") a better explanation as of why)
