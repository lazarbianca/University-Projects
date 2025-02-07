# 3. permutation cipher
import math


# split plaintext into blocks of length len(key)
# if we reach the end of plaintext, pad with space
# rearrange the character at the kth index (k - digit in key)
# to be placed in the pth index (p - index of digit in key)

def permutation_cipher(plaintext, key, decrypt):
    final_message = ''
    key_string = str(key)
    key_length = len(key_string)
    # len(plaintext) % key_length  => how much the message exceeds the block
    # key_length - (len(plaintext) % plaintext)  => how many spaces to add to fill the last block
    # % key_length at the end for the case where plaintext is already divisible with key_length
    plaintext_length = len(plaintext)
    plaintext += ' ' * ((key_length - (plaintext_length % key_length)) % key_length)
    plaintext_length = len(plaintext)

    number_of_blocks = int(plaintext_length/key_length)

    for block_index in range(number_of_blocks):
        start_index = block_index * key_length
        end_index = start_index + key_length
        # copy current block
        block = [x for x in plaintext[start_index:end_index]]

        # encrypt / decrypt - depending on parameter value
        new_block = [' '] * key_length
        for position, key_value in enumerate(key_string):
            # print(f"position: {position}, key_value: {key_value}, {new_block}")
            key_value = int(key_value) - 1
            if decrypt:
                new_block[key_value] = block[position]
            else:
                new_block[position] = block[key_value]

        # join the new block into the final_message
        final_message += ''.join(new_block)
    return final_message

if __name__ == '__main__':
    key = 523641
    plaintext = 'Implement one of the following algorithms, which will be assigned to you during the labs:'
    plaintext = 'ana are mere'
    print(plaintext)

    encrypted = permutation_cipher(plaintext, key, False)
    print(encrypted)

    decrypted = permutation_cipher(encrypted, key, True)
    print(decrypted)
