#!/usr/bin/env ruby

class Quaternion

  attr_accessor :state, :sign
  
  def initialize()
    @state = '1'
    @sign = 1
  end

  # another initializer
  def self.new2(state, sign)
    ret = self.new
    ret.state = state
    ret.sign = sign
    return ret
  end

  def mulTable(ch1, ch2)
    if (ch1 == '1') then 
      return [ch2, 1]
    elsif (ch1 == 'i') then
      table = {
        '1' => ['i', 1],
        'i' => ['1', -1],
        'j' => ['k', 1],
        'k' => ['j', -1]
      }
      return table[ch2]
    elsif (ch1 == 'j') then
      table = {
        '1' => ['j', 1],
        'i' => ['k', -1],
        'j' => ['1', -1],
        'k' => ['i', 1]
      }
      return table[ch2]
    else
      table = {
        '1' => ['k', 1],
        'i' => ['j', 1],
        'j' => ['i', -1],
        'k' => ['1', -1]
      }
      return table[ch2]
    end
  end
  private :mulTable

  # self * ch
  def mul(ch)
    res = mulTable(@state, ch)
    @state = res[0]
    @sign *= res[1]
  end

  # ch * self
  def mul_rev(ch)
    res = mulTable(ch, @state)
    @state = res[0]
    @sign *= res[1]
  end

  def pow(n)
    newsign = (@sign == 1) ? 1 : ((n % 2 == 1) ? -1 : 1)
    if @state == '1' then
      return Quaternion.new2('1', newsign)
    end

    case n % 4
    when 0
      return Quaternion.new2('1', newsign)
    when 1
      return Quaternion.new2(@state, newsign)
    when 2
      return Quaternion.new2('1', -1 * newsign)
    else
      return Quaternion.new2(@state, -1 * newsign)
    end

    return ret
  end

  def same(q)
    return @state == q.state && @sign == q.sign
  end

  def debug_print()
    print (@sign == 1 ? "" : "-"), @state, "\n"
  end

end

def solve()
  l,x = gets.split.map {|s| s.to_i}
  str = gets.chomp

  q = Quaternion.new
  str.each_char do |ch|
    q.mul(ch)
    # print "ch: ", ch, ".\n"
    # q.debug_print()
  end

  all = q.pow(x)
  shouldbe = Quaternion.new2('1', -1)
  return "NO" if (!all.same(shouldbe))

  willGoI = Quaternion.new
  i = Quaternion.new2('i', 1)
  lenI = 0
  found = false

  [16,x].min.times do |rep|
    break if found
    str.each_char do |ch|
      willGoI.mul(ch)
      lenI += 1
      if willGoI.same(i) then
        found = true
        break
      end
    end
  end
  return "NO" if (!found)

  willGoK = Quaternion.new
  k = Quaternion.new2('k', 1)
  lenK = 0
  found = false
  str.reverse!
  [16,x].min.times do |rep|
    break if found
    str.each_char do |ch|
      willGoK.mul_rev(ch)
      lenK += 1
      if willGoK.same(k) then
        found = true
        break
      end
    end
  end
  
  return "NO" if (!found)
  return "YES" if lenI + lenK < l * x
  return "NO"
  
end

def main()
  testnum = gets.to_i
  testnum.times do |t|
    print "Case ##{t+1}: ", solve(), "\n"
  end
end

main()
