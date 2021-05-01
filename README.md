# C++ Linked-List Search Engine

### Console application for searching words from files
- Developed with C++
- Linked lists from data structures are used



**Description**
- It reads 400.000 words from 4 different file(pdf,html,docx,txt) words put on double-linked-lists sorted by the number of letter. While it's searching it looks lenght of the word and find the true list and find the word. If it can't find the exact word, it uses levensthein distance algorithm and find the common words.


**Additional libraries**
- pdfdoc.exe: it turns the metin2.pdf and metin4.docx to txt file then read from it, and delete txt file. SharpZipLib.dll and itextsharp.dll are library of pdfdoc.exe. It contains classes.

- distance.h:It finds levensthein distance values. Levensthein algorithm library.




## Turkish

**C++ Bağlı liste ile arama motoru tasarımı**

400.000 kelime okunur ve listelere harf sayılarına göre dizilir. Ararken arananın harf sayısına göre listelere bakar ve eşleşen'i bulup sayisini ve hangi dosyada kaç tane olduğunu yazar. Tam eşleşme bulamazsa arananın harf sayısından 2 alt ve 2 üst listede levenshtein derecesi 2 ve altı olanları bulur ve yazar.

pdfdoc.exe: metin2.pdf ve metin4.docx'i txt formatına çevirip okur,okuduktan sonra txt,ler silinir. SharpZipLib.dll ve itextsharp.dll bu exenin dosyalarıdır. Classları içerir

distance.h : levenshtein distance değerlerini bulur levenshtein algoritmasının kütüphanesidir.
