import re
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
            pattern = ['date', 'to', 'from']
            d, f, t = [re.search('{}:(.+?);'.format(p), postcard).group(1) for p in pattern]

            for var, attr in zip([d, f, t], [self._date, self._to, self._from]):
                if var in attr:
                    attr[var].append(self._postcards.index(postcard))
                else:
                    attr[var] = [self._postcards.index(postcard)]

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
        date_range_postcards = []
        for date in self._date:
            if date_range[0].date() <= date <= date_range[1].date():
                for j in self._date[date]:
                    date_range_postcards.append(self._postcards[j])
        return date_range_postcards

    def getPostcardsBySender(self, sender):
        sender_postcards = []
        if sender in self._from:
            for i in self._from[sender]:
                sender_postcards.append(self._postcards[i])
        return sender_postcards
    
    
    def getPostcardsByReceiver(self, receiver):
        receiver_postcards = []
        if receiver in self._to:
            for i in self._to[receiver]:
                receiver_postcards.append(self._postcards[i])
        return receiver_postcards
                
