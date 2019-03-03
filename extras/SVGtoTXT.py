#!/usr/bin/env python3

if __name__ == "__main__":
    print("We are main!")
    # load file TODO: load file from command-line input
    inp = open("test.svg", "r")

    # find line points string
    # TODO: actually parse the SVG, rather than regex
    line = ""
    while True:
        line = inp.readline()
        #TODO: REGEX search for "d=m" characters
        if(line.contains("d=m")):
            break
    
    # Split string along spaces
    spline = line.split(" ")
    # delete non-integer values ("m" and "c")
    del spline[0]
    del spline[1]
    # split string list into list coord-pair string tuples
    strparts = []
    for part in spline:
        strparts.append(part.split(","))
    # convert strings to actual integers
    intparts = []
    for part in strparts:
        intparts.append( (float(part[0]), float(part[1])) )
    # add point delta's to root coord
    for coord in intparts[1:]:  # skip first -- root doesn't add to itself :v
        coord[0] = coord[0] + intparts[0][0]
        coord[1] = coord[1] + intparts[0][1]
    # write output values to file
    outp = open("coords.txt", "w")
    for coord in intparts:
        outp.write( str(coord[0]) + "," + str(coord[1]) )
    outp.flush()
    
    # do cleanup
    inp.close()
    outp.close()

