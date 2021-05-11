/*
 * FreeRTOS V202012.00
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

/*
 * PEM-encoded client certificate
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWTCCAkGgAwIBAgIUIrFw+v4kjxxH7x4vauXRCtQLvvwwDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIxMDUwMzE4MDMw\n"\
"M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"\
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJuui/QqhqFn0NELs8l+\n"\
"Ga7UpDlZS5CZgWbfCvAHb7qULGx9TjpQHkS/n9oCDPn/cOqFAOC7Pk8tIOp0GqvN\n"\
"d/IuOgFcWyr63XMlz4qS7ft16iptj5veSPjJcPMnAeEEB0Q3RM8kHvbbhURTLApD\n"\
"y9LEuPLLjT4qoJ40+BVYUJga3PQUmyid+OVN4aXLmoKfHz1/JkNvK6heUyXn8PCJ\n"\
"1Kk7it0ocOnhYlKiZgALlTyZmZH/jbEX1ipu5ZLM6fpohabho/bPqCmXc1R9RnAX\n"\
"4nUPI3vTWYRoBbTL78XZ2W/WXrDe8WIUqWFUZQeeSSTIthLwTYNtThvVpclidXzI\n"\
"LJcCAwEAAaNgMF4wHwYDVR0jBBgwFoAUZFPIhp2RagH19ehznOtyEg/fx5QwHQYD\n"\
"VR0OBBYEFMzfwTgqX6U3AVXoesq9u7HWXpbXMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"\
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCDcei3Zh+wnVkgY1eNwHZ0Rf2Y\n"\
"E5wZIBrpYYaBpIeHj7RJmu0+U3FVY0MLLC2E/VIYJXH8rmbAyWNUcnOd9VGf/GI9\n"\
"Z7qPc2YSxmq+VNZRkPmHnLOZc2PAJaF7kTEuNuuHZoALevK5AfEydNYeWE5FSrQI\n"\
"sSD5YoAsy0La8VWr9OesYVbwxrTcdSFsxGgcy8KCVbqMegm2LHf3VJw6XmM2N73w\n"\
"1Qtv4ZH4PiuFW7YNNp68tI49XooPZPTSrMAzab95HBtD5pxaiTbvTAtzrIacGWYr\n"\
"tNk3h1lNHq/IY2QE1/jWKi0QwUB9IgJH0oLE7o56o4cPJ24vxJyQQ09cUMyT\n"\
"-----END CERTIFICATE-----\n"

/*
 * PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 * This is required if you're using JITR, since the issuer (Certificate
 * Authority) of the client certificate is used by the server for routing the
 * device's initial request. (The device client certificate must always be
 * sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html,
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set below to NULL.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM  ""

/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEowIBAAKCAQEAm66L9CqGoWfQ0QuzyX4ZrtSkOVlLkJmBZt8K8AdvupQsbH1O\n"\
"OlAeRL+f2gIM+f9w6oUA4Ls+Ty0g6nQaq8138i46AVxbKvrdcyXPipLt+3XqKm2P\n"\
"m95I+Mlw8ycB4QQHRDdEzyQe9tuFRFMsCkPL0sS48suNPiqgnjT4FVhQmBrc9BSb\n"\
"KJ345U3hpcuagp8fPX8mQ28rqF5TJefw8InUqTuK3Shw6eFiUqJmAAuVPJmZkf+N\n"\
"sRfWKm7lkszp+miFpuGj9s+oKZdzVH1GcBfidQ8je9NZhGgFtMvvxdnZb9ZesN7x\n"\
"YhSpYVRlB55JJMi2EvBNg21OG9WlyWJ1fMgslwIDAQABAoIBACxwwxrMGOpyTDWg\n"\
"dY4LJSG3KboFN4DrkPjgqqqiNM66BYRisLYMsNdHLEZ7V2D1/jG0DfAZA0xuwXqr\n"\
"8gEhAiBr+brxtkSqoBSCsqAIGU8y9cluxRPlfEcomcmPVQX6tGhQrp/C2+Pz/jLm\n"\
"2yeC+ugLqBAG8ybP3FHNJRRSxY7lijChotJB0eWXhOMGoo9EWf9mAJ63aPUXiCd3\n"\
"FC4Mn+Mx6tmp5Lcs/E6GoqCqqmMPHh3bC1mFu5+rDVkrM+Q0NlDYbi1QEpT9ERut\n"\
"sQZrOnkOtnB6BrerT3tGTXZN3N8o9B1+Px6iy/OJia6q1W2N1xeDVavdNafRoFw5\n"\
"onb35qECgYEAzRmbS410sKDQOqTD2Kr1kQn0kUiFNJ8jnXW7Vv7Z2HAY4Xu+c2du\n"\
"L6hIqXInc1kyfpQEyySSA/PjwkPrwHn3EiBm8tM/1xodUoM9PdlTWAVmOjR8eD/9\n"\
"BmS/EUiXIR6AfwdtDxdlLqFJ7M2ctCuspNlJld+L2C86k+ObWBw9gRUCgYEAwlFO\n"\
"1+ZqFmlBBpfHlcEEPFHdc7DbFM43oKDp1A7nyhZoegonniUaGEoVoRYcd/beP97t\n"\
"qVzVOjEyj66o7w1G/xZlr80oXf2xU/w7+TTlescckz6vSh49P+uj4B+B14DSPmBX\n"\
"DhGD0c2YVBkaUj6iYWUUEETD0+RLs0nczuClafsCgYEAu0SZLgfvtuJunk0Y4Tlf\n"\
"1NlxLEI6Fg0EGN6JempiACSCI0e4YmjbC7qs9cJcUQ7tcvO12MIAbImAuT0JAgqa\n"\
"1DsvpKHMFZwrj85y2YkYdzMe3yBTUfyjC/ZrGt3b2Aqgqtvd8TycT1JHTGeEoGGM\n"\
"VkxryuN9LZwZ8TSN/4pxge0CgYA0zQMvh1ysWk1hDT0eZCRSf6w9E4F0VdSnwRHI\n"\
"nYQ+VXhuMPQy9MHyd68I5ok1z870bA8IRkFqXpPulvcwfdsc1WksLAMcByN4PsHN\n"\
"JaJ1ikUpfY8EBNN/2vfcnrMZa9e1O1hsajX3fHY349pTHtHgxSZ+hTDxEse/IALv\n"\
"8/r+oQKBgDj7u45prT0Xz8UdY3LQBDWPptWJPxpNKOEtpOPNyMCz0o9eLDmycK4n\n"\
"Z+7zQFmlQii7eZE+tIL+iGmZNSlp4oQ85x71MIF6aB6Q8HNzb3uIJLHQXg7FUr4J\n"\
"U1eDG67xLGj7UvXXmuaO9CoYLFU9KzQouKcqJkyNLycXdIpynj0m\n"\
"-----END RSA PRIVATE KEY-----\n"

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
