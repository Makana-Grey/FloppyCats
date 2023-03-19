import randomString from 'randomized-string'

/**
 * @param {String} name
 * @returns {String}
 */
export function generateToken(name) {
    return name + '-' + randomString.generate(128)
}
