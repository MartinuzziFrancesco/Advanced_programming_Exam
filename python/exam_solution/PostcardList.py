from datetime import date


class PostcardList:

    def __init__(self):
        self._file = ''
        self._postcards = []
        self._date = {}
        self._from = {}
        self._to = {}
        self._unparsed = 0

    def writeFile(self, _date, _from, _to):  # write self.{_date,_from,_to} to self._file
        try:
            f = open(self._file, 'w')
            f.write('date:{}; from:{}; to:{};\n'.format(_date, _from, _to))
            f.close()
        except OSError:
            print('Something went wrong in opening or in writing {}.\n'.format(self._file))

    def readFile(self, file):  # from self._file read self.{_date,_from,_to}
        try:
            self._file = file
            f = open(self._file, 'r')
            self._postcards = []
            for line in f:
                self._postcards.append(line)
                self._unparsed += 1
        except OSError:
            print('Something went wrong in opening or in reading {}.\n'.format(self._file))

    def parsePostcards(self):  # parse self._postcards, set self.{_date,_from,_to}
        for postcard in self._postcards[-self._unparsed:]:
            d, f, t = postcard.split()
            d = d[5:-1]
            f = f[5:-1]
            t = t[3:-1]
            if d in self._date:
                self._date[d].append(self._postcards.index(postcard))
            else:
                self._date[d] = [self._postcards.index(postcard)]

            if f in self._from:
                self._from[f].append(self._postcards.index(postcard))
            else:
                self._from[f] = [self._postcards.index(postcard)]

            if t in self._to:
                self._to[t].append(self._postcards.index(postcard))
            else:
                self._to[t] = [self._postcards.index(postcard)]
        self._unparsed = 0

    def updateFile(self, _date, _from, _to):  # write self.{_date,_from,_to} to self._file
        try:
            f = open(self._file, 'a+')
            f.write('date:{}; from:{}; to:{};\n'.format(_date, _from, _to))
            f.close()
        except OSError:
            print('Something went wrong in opening or in writing {}.\n'.format(self._file))

    def updateLists(self):  # as read but appending to self._postcards
        try:
            f = open(self._file, 'r')
            for line in f.readlines()[len(self._postcards):]:
                self._postcards.append(line)
                self._unparsed += 1
        except OSError:
            print('Something went wrong in opening or in reading {}.\n'.format(self._file))

    def getNumberOfPostcards(self):
        return len(self._postcards)

    def getPostcardsByDateRange(self, date_range):
        pass

    def getPostcardsBySender(self, sender):
        pass

    def getPostcardsByReceiver(self, receiver):
        pass
