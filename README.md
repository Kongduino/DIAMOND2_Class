Diamond2 Class - Arduino implementation of the Diamond2 and Diamond2 Lite Block Ciphers
====================================================

Introduction
------------------------
This is an Arduino-based implementation of the Diamond2 and Diamond2 Lite Block Ciphers by Michael Paul Johnson, as a class. It has been written with the nRF52840 – and specifically the [Wisblock RAK4631](https://store.rakwireless.com/products/rak4631-lpwan-node?variant=37505443823814) – in mind, both for the [Arduino BSP](https://docs.rakwireless.com/Knowledge-Hub/Learn/Installation-of-Board-Support-Package-in-Arduino-IDE/) and the [RUI3 platform](https://docs.rakwireless.com/RUI3/).

However, it should work with any reasonably powerful MCU – this is OLD code, and was running before most of us had access to the Internet (Diamond2 was released in 1995). There's one example so far, which does a round trip as a sanity check. I will add more examples and test them on various MCUs.

