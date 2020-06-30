from datetime import datetime


class PostcardList:
    def __init__(self):
        self._file = ""
        self._postcards = []
        self._date = {}
        self._from = {}
        self._to = {}

    def writeFile(self, filename):
        f = open(filename, "w")
        for postcard in self._postcards:
            f.write(postcard)
        f.close()

    def readFile(self, new_file):
        self._postcards = []
        self._file = new_file
        f = open(self._file, "r")
        for line in f:
            self._postcards.append(line)
        f.close()
        self.parsePostcards()

    def parsePostcards(self):
        for i in range(0, len(self._postcards)):
            date, sender, receiver = self._postcards[i].split(" ")
            date = date[5:15]
            sender = sender[5:-1]
            receiver = receiver[3:-2]
            date = datetime.strptime(date, "%Y-%m-%d")
            if date not in self._date:
                self._date[date] = []
            self._date[date].append(i)
            if sender not in self._from:
                self._from[sender] = []
            self._from[sender].append(i)
            if receiver not in self._to:
                self._to[receiver] = []
            self._to[receiver].append(i)

    def updateFile(self, filename):
        f = open(filename, "a")
        for postcard in self._postcards:
            f.write(postcard)
        f.close()

    def updateLists(self, new_file):
        self._file = new_file
        f = open(self._file, "r")
        for line in f:
            self._postcards.append(line)
        f.close()
        self.parsePostcards()

    def getNumberOfPostcards(self):
        return len(self._postcards)

    def getPostcardsByDateRange(self, date_range):
        postcards_by_date = []
        for i in self._date:
            if date_range[0] <= i <= date_range[1]:
                for j in self._date[i]:
                    postcards_by_date.append(self._postcards[j])
        return postcards_by_date

    def getPostcardsBySender(self, sender):
        postcards_by_sender = []
        if sender in self._from:
            for i in self._from[sender]:
                postcards_by_sender.append(self._postcards[i])
        return postcards_by_sender

    def getPostcardsByReceiver(self, receiver):
        postcards_by_receiver = []
        if receiver in self._to:
            for i in self._to[receiver]:
                postcards_by_receiver.append(self._postcards[i])
        return postcards_by_receiver
