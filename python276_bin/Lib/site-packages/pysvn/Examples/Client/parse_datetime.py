'''
 ====================================================================
 Copyright (c) 2003-2009 Barry A Scott.  All rights reserved.

 This software is licensed as described in the file LICENSE.txt,
 which you should have received as part of this distribution.

 ====================================================================
'''

_debug_parse_time = 0

class DateTimeSyntaxError( Exception ):
    def __init__( self, reason ):
        Exception.__init__( self )
        self._reason = reason

    def reason( self ):
        return self._reason

    def __str__( self ):
        return self._reason


class DateSyntaxError( DateTimeSyntaxError ):
    def __init__( self, reason ):
        DateTimeSyntaxError.__init__( self, reason )

class TimeSyntaxError( DateTimeSyntaxError ):
    def __init__( self, reason ):
        DateTimeSyntaxError.__init__( self, reason )

def parse_time( time_string ):
    """parse_time( time_string )
    returns the UTC time represented by time_string

    british locale defaults used

    formats understood for a date are:
        dayname         - today, yesterday, monday, tuesday...
        dd/mm/yy[yy]    - numeric date
        dd-mmm-yy[yy]   - month as jan,feb,etc...
        n units         - n units of time ago
                          where units are:
                            seconds
                            minutes
                            hours
                            days
                            weeks
                            months
                            years
                    

    formats understood for time are:
        HH:MM           - absolute time in hours and minutes
        HH:MM:SS        - absolute time in hours, minutes and seconds

    formats understood for data and time are:
        adate atime     - absolute date followed by absolute time
        rdate atime     - relative date followed by absolute time
        atime adate     - absolute time followed by absolute date
        atime rdate     - absolute time followed by relative date
    
    """
    if _debug_parse_time: print( '* parse_time: time_string=',time_string )

    date = DateConversions()

    have_date = 0
    have_time = 0

    table = string.maketrans("-/","  ")

    time_list = string.split( string.translate( time_string, table ) )
    
    try:
        day_time = convert_time( time_list[0] )
        time_list = time_list[1:]
        if _debug_parse_time:
            print( '* parse_time: Time_list[0] is a time' )
    except TimeSyntaxError:
        try:
            day_time = convert_time( time_list[-1] )
            time_list = time_list[:-1]
            if _debug_parse_time:
                print( '* parse_time: Time_list[-1] is a time' )
        except TimeSyntaxError:
            day_time = 0
            
    if len(time_list) == 0:
        # default to today at time
        result = date.midnight + day_time
        if _debug_parse_time: print( '* parse_time: 1 return',format_time(result) )
        return result

    match_type = date.numeric_type
    matches = []
    for word in time_list:
        day_matches = date.findMatchingDateName( word )
        if len(day_matches) == 0:
            raise DateSyntaxError( "%s unknown date word" % word )

        if date.isAmbiguous( day_matches ):
            raise DateSyntaxError( date.reportAmbiguity( word, day_matches ) )

        this_type = date.typeOfMatch( day_matches )
        if this_type != date.numeric_type:
            if match_type == date.numeric_type:
                match_type = this_type
            elif match_type != this_type:
                raise DateSyntaxError( "ambiguous mix of unit and month names" )

        matches.append( day_matches[0] )
    if _debug_parse_time: print( '* parse_time: matches=',matches )

    if match_type == date.day_type:
        if len(matches) != 1:
            raise DateSyntaxError( "too many day words" )

        day_matches = matches[0]

        result = date.convertDay( day_matches[2] ) + day_time
        if _debug_parse_time: print( '* parse_time: 2 return',format_time(result) )
        return result

    if match_type == date.unit_type:
        # expect a set of pair of <num> <unit>
        if _debug_parse_time >= 2:
            print( 'matches',matches )
        if (len(matches)&1) == 1:
            raise DateSyntaxError( 'must have an even number parameters when using time units' )

        time_offset = 0
        for index in range( 0, len(matches), 2 ):
            value_tuple = matches[index]
            unit_tuple = matches[index+1]

            if value_tuple[1] != date.numeric_type:
                raise DateSyntaxError( 'Expecting a number of units' )
            if unit_tuple[1] != date.unit_type:
                raise DateSyntaxError( 'Expecting a unit name' )

            value = value_tuple[2]
            unit = unit_tuple[2]
            time_offset = time_offset + value*unit

        result = date.now - time_offset
        if _debug_parse_time: print( '* parse_time: 3 return',format_time(result) )
        return result

    if match_type == date.month_type:
        # absolute date
        if len(matches) < 1 or len(matches) > 3:
            raise DateSyntaxError( 'too many date parts' )
        
        day = -1
        month = -1
        year = -1

        num_month_types = 0
        for entry in matches:
            if date.isMonth( entry ):
                num_month_types = num_month_types + 1

        if num_month_types != 1:
            raise DateSyntaxError( 'too many months in the date string' )


        if date.isMonth( matches[0] ):
            month = matches[0][2]
            day = matches[1][2]
            if len(matches) == 3:
                year = matches[2][2]
        else:
            day = matches[0][2]
            if matches[1][1] != date.month_type:
                raise DateSyntaxError( 'expecting month as first or second part of date' )
            month = matches[1][2]
            if len(matches) == 3:
                year = matches[2][2]

        seconds = day_time%60
        minutes = (day_time/60)%60
        hours = day_time/60/60

        result = date.absDate( day, month, year, hours, minutes, seconds )
        if _debug_parse_time: print( '* parse_time: 4 return',format_time(result) )
        return result

    if match_type == date.numeric_type and len(matches) == 3:
        # assume its in locale order - which is assumed to be D M Y
        day = matches[0][2]
        month = matches[1][2]
        year = matches[2][2]

        seconds = day_time%60
        minutes = (day_time/60)%60
        hours = day_time/60/60

        result = date.absDate( day, month, year, hours, minutes, seconds )
        if _debug_parse_time: print( '* parse_time: 4 return',format_time(result) )
        return result

    raise DateSyntaxError( 'cannot understand date and time string ' + time_string )


def convert_time( time_str ):
    time_list = string.split( time_str, ':' )
    if len(time_list) < 2:
        # not a time - no ":"
        raise TimeSyntaxError( "Not a time" )

    if len(time_list) > 3:
        raise TimeSyntaxError( "Too many time parts" )

    hour = time_list[0]
    minute = time_list[1]
    second = '0'
    if len(time_list) > 2:
        second = time_list[2]

    try:
        hour = string.atoi( hour )
        minute = string.atoi( minute )
        second = string.atoi( second )
    except:
        return -1

    if( hour < 0 or hour > 23 ):
        raise TimeSyntaxError( "hour value of %d invalid" % hour )
    if( minute < 0 or minute > 59 ):
        raise TimeSyntaxError( "minutes value of %d invalid" % hour )
    if( second < 0 or second > 59 ):
        raise TimeSyntaxError( "seconds value of %d invalid" % hour )

    day_time = (hour*60 + minute)*60 + second

    return day_time


class DateConversions:
    seconds_in_one_day = 24*60*60

    day_type = 1
    month_type = 2
    unit_type = 3
    numeric_type = 4

    date_names = [
        # day names
        ('today',       day_type,    0),
        ('yesterday',   day_type,    -1),
        ('monday',      day_type,    1),
        ('tuesday',     day_type,    2),
        ('wednesday',   day_type,    3),
        ('thursday',    day_type,    4),
        ('friday',      day_type,    5),
        ('saturday',    day_type,    6),
        ('sunday',      day_type,    7),
        # month names
        ('january',     month_type,    1),
        ('feburary',    month_type,    2),
        ('march',       month_type,    3),
        ('april',       month_type,    4),
        ('may',         month_type,    5),
        ('june',        month_type,    6),
        ('july',        month_type,    7),
        ('august',      month_type,    8),
        ('september',   month_type,    9),
        ('october',     month_type,    10),
        ('november',    month_type,    11),
        ('december',    month_type,    12),
        # unit names
        ('seconds',     unit_type,    1),
        ('minutes',     unit_type,    60),
        ('hours',       unit_type,    60*60),
        ('days',        unit_type,    24*60*60.),
        ('weeks',       unit_type,    7*24*60*60),
        ('months',      unit_type,    30*24*60*60),
        ('years',       unit_type,    365*24*60*60)
        ]

    def __init__( self ):
        self.now = time.time()
        self.year, self.month, self.day, self.hour, self.minute, self.second, self.weekday, self.julian, self.dst = time.localtime( self.now )
        
        self.midnight = time.mktime( 
                (self.year, self.month, self.day,
                0, 0, 0,
                self.weekday, self.julian, self.dst) )

    def convertDay( self, day_offset ):
        if day_offset == 0:    # today
            return self.midnight
        elif day_offset == -1:    # yesterday
            return self.midnight - self.seconds_in_one_day
        else:
            # day of week
            offset = day_offset - self.weekday - 1
            # make sure its in the past
            if offset >= 0:
                offset = offset - 7

            return self.midnight + offset*self.seconds_in_one_day

    def absDate( self, day, month, year, hour=0, minute=0, second=0 ):
        future_check = 0
        if year < 0:
            year = self.year
            future_check = 1
        elif year < 70:
            year = year + 2000
        elif year < 100:
            year = year + 1900

    
        try:
            date = time.mktime( 
                (year, month, day,
                hour, minute, second,
                self.weekday, self.julian, -1) )
        except OverflowError:
            raise DateSyntaxError( 'cannot convert date and time year=%d/month=%d/day=%d %d:%d:%d' %
                           (year, month, day, hour, minute, second) )

        if date > self.now and future_check:
            year = year - 1

            try:
                date = time.mktime( 
                    (year, month, day,
                    hour, minute, second,
                    self.weekday, self.julian, -1) )
            except OverflowError:
                raise DateSyntaxError( 'cannot convert date and time %d/%d/%d %d:%d:%d' %
                    (year, month, day, hour, minute, second) )

        return date

    def findMatchingDateName( self, name ):
        try:
            value = string.atoi( name )
            return [(name, self.numeric_type, value )]
        except:
            pass

        matches = []
        name_len = len(name)
        for entry in self.date_names:
            entry_name = entry[0]
            if len(entry_name) >= name_len and entry_name[0:name_len] == name:
                matches.append( entry )

        return matches


    def typeOfMatch( self, matches ):
        return matches[0][1]

    def isAmbiguous( self, matches ):
        return len(matches) > 1

    def isDay( self, matches ):
        return matches[1] == self.day_type

    def isMonth( self, matches ):
        return matches[1] == self.month_type

    def isUnit( self, matches ):
        return matches[1] == self.unit_type

    def isNumeric( self, matches ):
        return matches[1] == self.numeric_type

    def reportAmbiguity( self, name, tuples ):
        names = map( lambda t: t[0], tuples )
        return "%s is ambiguous, it matches: %s" % (name, string.join( names, ', ' ))

