text = STDIN.read
text.gsub!/\<tr class="saying"\>\s*\<td class="who"\>([^\<]+)\<\/td\>\s*\<td class="text"\>([^\<]+)\<\/td\>\s*\<\/tr\>/ { "<li><b>#{$1}</b> #{$2}</li>\n" }
print text
