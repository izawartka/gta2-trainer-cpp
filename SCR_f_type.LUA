--Note: keep the function base name unique.
typename="SCR_f" --shown as the typename in ce
bytecount=4  --number of bytes of this type
functionbasename="SCR_f"

function SCR_f_bytestovalue(b1,b2,b3,b4,address)
--Add extra byte parameters as required
local a = b1 * 256 * 256 * 256 + b2 * 256 * 256 + b3 * 256 + b4
return b4 / 16384.0

end

function SCR_f_valuetobytes(i,address)

--return the bytes to write (usually only used when you change the value)
return 0,0,0,0

end
return typename,bytecount,functionbasename
