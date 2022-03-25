/*
KH5004CEM Operating Systems and Security
Task #2
Mariam Abdelaty
CU2000406
*/

/*
    One of the first IPC mechanisms in early UNIX systems were Pipes. Pipes acts as a
conduit allowing two processes to communicate, they typically provide one of the simpler ways
for processes to communicate with one another. Ordinary pipes are the most common type of
pipes. Ordinary pipes allow two processes to communicate in standard producer– consumer
fashion: the producer writes to one end of the pipe (the write-end) and the consumer reads
from the other end (the read-end). As a result, ordinary pipes are unidirectional, allowing only
one-way communication. If two-way communication is required, two pipes must be used, with
each pipe sending data in a different direction. 

    Design a program using ordinary pipes such that
one process sends a string message to the second process. The second process should then
reverse the case of each character in the message and sends it back to the first process. As an
example, if the first process sends the message Hi There, the second process will return hI
tHERE. This will require using two pipes, one for sending the original message from the first to
the second process and the other for sending the modified message from the second to the
first process
*/