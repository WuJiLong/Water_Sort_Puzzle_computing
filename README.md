# Water_Sort_Puzzle_computing

## command
- start 開始計算  
- exit 離開程式  
- reset 重置，清空所有瓶子  
  顏色名稱並不會受到此影響  
- setbottle [bottle-id] [type]  
  ex: setbottle 12 A B C D  
  12  
  |D|  
  |C|  
  |B|  
  |A|  
  |-\|  
  ex: setbottle 9 A B B  
  9  
  |&nbsp;|  
  |B|  
  |B|  
  |A|  
  |-\|  
- setcolor [bottle-id] [loc] [type]  
  ex: setcolor 4 1 H  
  將4號瓶子中的第1格填上色彩代號  
  4  
  |&nbsp;|  <--- loc = 3  
  |&nbsp;|  <--- loc = 2  
  |H|  <--- loc = 1  
  |&nbsp;|  <--- loc = 0  
  |-\|  
- renamecolor [type] [name]  
  ex: renamecolor A 彩色  
  A：彩色  
- clear [bottle-id] \<loc\>  
  ex: clear 6 2  
  刪除6號瓶子中的第2格  
  6  
  |D|  <--- loc = 3  
  |&nbsp;|  <--- loc = 2  
  |B|  <--- loc = 1  
  |A|  <--- loc = 0  
  |-\|  
  ex: clean 8  
  清空8號瓶子  
  8  
  |&nbsp;|  
  |&nbsp;|  
  |&nbsp;|  
  |&nbsp;|  
  |-\|  
## 命令縮寫
- start　-> s  
- exit -> e  
- reset -> r  
- setbottle [bottle-id] [type] -> sb [bottle-id] [type]    
- setcolor [bottle-id] [loc] [type] -> sc [bottle-id] [loc] [type]  
- renamecolor [type] [name] -> rn [type] [name]  
- clear [bottle-id] \<loc\> -> c [bottle-id] \<loc\>  
## 快速測試指令
 a.out \< testdata  
