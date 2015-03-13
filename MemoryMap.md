# MEGA WINCE MEMORY MAP #

v80000000-85500000 -> p00300000-05800000   5500000 -> 85M Bank0 <br>
v85500000-87f00000 -> p08000000-0aa00000   2a00000 -> 42M Bank1 <br>
v88000000-88100000 -> p00000000-00100000    100000 ->  1M SPL  <br>
v8a000000-8a100000 -> p07f00000-08000000    100000 ->  1M SMEM <br>
v8a100000-8e000000 -> p0aa00000-0e900000   3f00000 -> 63M Bank1 <br>
v8e000000-8e200000 -> p00100000-00300000    200000 ->  2M ??? try to add to bank0! <br>
v8e200000-8f900000 -> p0e900000-10000000   1700000 -> 23M Bank1 <br>
v90000000-90d00000 -> pac000000-acd00000    d00000 -> 13M AD5 <br>
v90d00000-90e00000 -> pa8000000-a8100000    100000 <br>
v90e00000-90f00000 -> pa0e00000-a0f00000    100000 <br>
v90f00000-91000000 -> pa0d00000-a0e00000    100000 <br>
v91000000-91100000 -> paa700000-aa800000    100000 ->  1M EMDH <br>
v91100000-91200000 -> pa0c00000-a0d00000    100000 <br>
v91200000-91400000 -> pa0a00000-a0c00000    200000 <br>
v91400000-91500000 -> pa0800000-a0900000    100000 ->  1M HSUSB <br>
v91500000-91600000 -> pa0700000-a0800000    100000 ->  1M SDC4 <br>
v91600000-91700000 -> pa0600000-a0700000    100000 ->  1M SDC3 <br>
v91700000-91800000 -> pa0500000-a0600000    100000 ->  1M SDC2 <br>
v91800000-91900000 -> pa0400000-a0500000    100000 ->  1M SDC1 <br>
v91900000-91b00000 -> pa0200000-a0400000    200000 ->  2M UART1/2DM <br>
v91b00000-91c00000 -> pa0100000-a0200000    100000 <br>
v91c00000-91d00000 -> paa600000-aa700000    100000 ->  1M PMDH <br>
v91d00000-91e00000 -> paa500000-aa600000    100000 ->  1M MDC <br>
v91e00000-91f00000 -> paa300000-aa400000    100000 ->  1M TSSC <br>
v91f00000-92000000 -> pa8100000-a8200000    100000 ->  1M SSBI <br>
v92000000-92100000 -> pa9d00000-a9e00000    100000 <br>
v92100000-92200000 -> pa9900000-a9a00000    100000 ->  1M I2C <br>
v92200000-92300000 -> pa8700000-a8800000    100000 <br>
v92300000-92400000 -> paa200000-aa300000    100000 ->  1M MDP <br>
v92400000-92500000 -> pa9c00000-a9d00000    100000 ->  1M UART3 <br>
v92500000-92600000 -> pa9b00000-a9c00000    100000 ->  1M UART2 <br>
v92600000-92700000 -> pa9a00000-a9b00000    100000 ->  1M UART1 <br>
v92700000-92800000 -> pa9800000-a9900000    100000 <br>
v92800000-92900000 -> pa9700000-a9800000    100000 ->  1M DMOV <br>
v92900000-92a00000 -> pa9600000-a9700000    100000 <br>
v92a00000-92b00000 -> pa9500000-a9600000    100000 <br>
v92b00000-92c00000 -> pa9400000-a9500000    100000 <br>
v92c00000-92d00000 -> pa9300000-a9400000    100000 ->  1M GPIO2 <br>
v92d00000-92e00000 -> pa9200000-a9300000    100000 ->  1M GPIO1 <br>
v92e00000-92f00000 -> pa9100000-a9200000    100000 <br>
v92f00000-93000000 -> pa9000000-a9100000    100000 <br>
v93000000-93100000 -> pa8600000-a8700000    100000 ->  1M CLK_CTL <br>
v93100000-93200000 -> pa8500000-a8600000    100000 <br>
v93200000-93300000 -> pa8300000-a8400000    100000 <br>
v93300000-93400000 -> pa8200000-a8300000    100000 <br>
v93400000-93500000 -> pa8200000-a8300000    100000 <br>
v93500000-93600000 -> pa8200000-a8300000    100000 <br>
v93600000-93700000 -> pa8200000-a8300000    100000 <br>
v93700000-93800000 -> pa8200000-a8300000    100000 <br>
v93800000-93900000 -> pa8000000-a8100000    100000 <br>
v93900000-93c00000 -> pc0000000-c0300000    300000 ->  1M VIC,  1M CSR,  1M ??? <br>
v93c00000-93f00000 -> pb0400000-b0700000    300000 <br>
v93f00000-94c00000 -> pb1000000-b1d00000    d00000 -> 13M hey 13M here ?  <br>
v94c00000-94f00000 -> pb8000000-b8300000    300000 <br>
v94f00000-95000000 -> pb0000000-b0100000    100000 <br>
v95000000-95200000 -> pb0200000-b0400000    200000 <br>
v96000000-96200000 -> p88000000-88200000    200000 <br>
v98000000-98200000 -> p8c000000-8c200000    200000 <br>
v9a000000-9a200000 -> p90000000-90200000    200000 <br>
v9c000000-9c100000 -> p94000000-94100000    100000 <br>
v9d000000-9d100000 -> p98000000-98100000    100000 <br>
v9e000000-9e200000 -> p9c000000-9c200000    200000 <br>
v9f000000-9f100000 -> p80000000-80100000    100000 <br>
vf0400000-f0500000 -> p00000000-00100000    100000 <br>
fffd0000-fffd4000 -> p00680000-00684000       4000 <br>
vffff0000-ffff1000 -> p00684000-00685000      1000 <br>
vffffc000-ffffd000 -> p00685000-00686000      1000 <br>
<blockquote><br>
Memory banks: <br>
Bank0: 00000000 - 05800000 ->  88M <br>
Bank1: 08000000 - 10000000 -> 128M <br>