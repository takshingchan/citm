#!/usr/bin/ruby
#
#  cilibrasi.rb
#
#  MIDI Preprocessor from Rudi Cilibrasi
#
#  Ported to mftext and refactored by Tak-Shing Chan.
#
#  Copyright (C) 2006, 2017 Rudi Cilibrasi and Tak-Shing Chan
#

chanbase = 0
chans = {}
div = 0.0
lastt = 0

# Extracts only MIDI note-on and note-off events
IO.popen('mftext ' + ARGV[0]).each do |line|
  div = $1.to_f if line =~ /division=(\d+)/
  if line =~ /(\d+)\s+Note\s+(o[nf]+),\s+chan=(\d+)\s+pitch=(\d+)\s+vol=(\d+)/
    t = ($1.to_f / div).round(2)
    c = $3.to_i
    n = $4.to_i
    v = $2 == 'off' ? 0 : $5.to_i
    chanbase += 40 if t < lastt
    lastt = t
    chans[c + chanbase] ||= { 'notes' => [] }
    chans[c + chanbase]['notes'] << [t, n, v]
  end
end

#
# These events were then converted to a player-piano style
# representation, with time quantised in 0.05-sec intervals.
#
chans.keys.each do |c|
  totvol = 0
  notecount = 0
  maxtime = 8.0                         # This can be tuned
  tstep = 0.05
  curt = 0
  multfactor = 0.5                      # This can be tuned
  laston = {}
  chans[c]['frames'] = []
  histogram = {}
  chans[c]['notes'].each do |t, n, v|
    while t.to_f * multfactor >= curt.to_f
      curt += tstep
      laston.delete_if { |d, _| laston[d][1] < curt - maxtime }
      chans[c]['frames'] << laston.keys.sort
    end
    if v > 0
      totvol += v
      notecount += 1
      laston[n] = [v, t * multfactor]
    elsif laston[n]
      histogram[n] ||= 0
      histogram[n] += laston[n][0] * (t * multfactor - laston[n][1])
      laston.delete(n)
    end
  end
  chans[c]['avgvol'] = totvol / notecount
  chans[c]['modalnote'] = histogram.keys.max_by { |p| histogram[p] }
end

#
# The modal note is used as a key-invariant reference point from
# which to represent all notes. The modal note is written as the
# first byte of each track. For each track, we iterate through
# each 0.05-sec time sample in order, producing a single signed
# 8-bit value as output for each currently sounding note (ordered
# from lowest to highest). Two special values are reserved to
# represent the end of a time step and the end of a track. The
# tracks are sorted according to decreasing average volume and
# then output in succession.
#
tracks = chans.keys.select  { |c| chans[c]['modalnote'] }
                   .sort_by { |c| -chans[c]['avgvol'] }
print tracks.size.chr
tracks.each do |c|
  mn = chans[c]['modalnote']
  print mn.chr
  chans[c]['frames'].each do |na|
    na.each { |n| print ((n - mn) & 255).chr }
    print 128.chr
  end
  print 127.chr
end
