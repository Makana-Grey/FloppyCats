import Router from 'koa-router'
import { default as connect } from './api/connect.js'
import { default as queries } from './api/queries.js'
import { default as states } from './api/states.js'

const router = new Router()

router
    .use('/connection', connect)
    .use('/players', queries)
    .use('/player', states)

export default router.routes()
