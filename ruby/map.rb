partition_size = 16
virtual = 65536
hint = 1
 
map = Array.new(partition_size).map!{Array.new(virtual, 0)}
 
(0...partition_size).each do |i|
  next if i == 0
  counter = Array.new(partition_size, 0)
  p "partition:#{i}"
 
  (0...virtual).each do |j|
    if i <= hint
      map[i][j] = j % i
      next
    end
    p "node:#{j}"
    k = map[i-1][j]
    counter[k] += 1
    if (counter[k] % i) == (i - 1)
      map[i][j] = i - 1
    else
      map[i][j] = map[i-1][j]
    end
  end
end

File.open("aaa", 'w') do |file| 
  map.each_with_index do |table, i|
    p i
    file.write(table.join(' '))
    file.write("\n")
  end
end
